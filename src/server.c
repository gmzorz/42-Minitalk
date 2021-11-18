/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 12:29:23 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/18 12:14:35 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

static void	showpid(void)
{
	pid_t	pid;

	pid = getpid();
	mt_putnbr(pid);
	mt_putstr("\n");
}

static bool	wait_for_header(void)
{
	t_sigcontext		*context;

	context = get_server_context();
	mt_memset(context, 0, sizeof(t_sigcontext));
	while (pause() == -1)
	{
		usleep(100);
		if (kill(context->pid, SIGUSR1) == -1)
			return (false);
		if (context->msg_length)
			break ;
	}
	context->message = (char *)malloc(context->msg_length);
	if (context->message == NULL)
		return (mt_error_free(CONTEXT_ALLOC_FAILURE, context));
	return (true);
}

static bool	wait_for_message(void)
{
	uint32_t			buf_pos;
	t_sigcontext		*context;

	context = get_server_context();
	buf_pos = 0;
	while (pause() == -1)
	{
		usleep(100);
		if (context->msg_pos == buf_pos + BUFFER_SIZE)
		{
			write(1, context->message + (buf_pos), BUFFER_SIZE);
			buf_pos += BUFFER_SIZE;
		}
		if (context->msg_pos == context->msg_length)
			break ;
		if (kill(context->pid, SIGUSR1) == -1)
			return (mt_error_free(NULL, context->message));
	}
	write(1, context->message + buf_pos, context->msg_length - buf_pos);
	free(context->message);
	while (kill(context->pid, SIGUSR2) != -1)
		usleep(100);
	return (true);
}

int	main(void)
{
	struct sigaction	usr1;
	struct sigaction	usr2;

	showpid();
	while (1)
	{
		mt_memset(&usr1, 0, sizeof(struct sigaction));
		mt_memset(&usr2, 0, sizeof(struct sigaction));
		usr1.sa_flags = SA_SIGINFO;
		usr2.sa_flags = SA_SIGINFO;
		usr1.__sigaction_u.__sa_sigaction = redirect_decode_header_usr1;
		usr2.__sigaction_u.__sa_sigaction = redirect_decode_header_usr2;
		sigaction(SIGUSR1, &usr1, NULL);
		sigaction(SIGUSR2, &usr2, NULL);
		if (wait_for_header() == false)
			continue ;
		usr1.__sigaction_u.__sa_sigaction = redirect_decode_signal_usr1;
		usr2.__sigaction_u.__sa_sigaction = redirect_decode_signal_usr2;
		sigaction(SIGUSR1, &usr1, NULL);
		sigaction(SIGUSR2, &usr2, NULL);
		wait_for_message();
	}
	return (EXIT_SUCCESS);
}
