/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decode.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 13:55:37 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/17 15:10:45 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>
#include <unistd.h>

void	*get_server_context(void)
{
	static t_sigcontext		context = (t_sigcontext){NULL, 0, 0, 0};

	return (&context);
}

void	decode_header(int signal, siginfo_t *info)
{
	static int32_t	header_length = 0;
	static int32_t	bitcount = 0;
	t_sigcontext	*context;

	context = get_server_context();
	context->pid = info->si_pid;
	if (signal == SIGUSR1)
		header_length |= 1UL << bitcount;
	else if (signal == SIGUSR2)
		header_length &= ~(1UL << bitcount);
	bitcount += 1;
	if (bitcount > 31)
	{
		context->msg_length = header_length;
		header_length = 0;
		bitcount = 0;
		return ;
	}
}

void	decode_signal(int signal, siginfo_t *info)
{
	static char		character = '0';
	static int32_t	bitcount = 0;
	t_sigcontext	*context;

	context = get_server_context();
	if (context->pid != info->si_pid)
		return ;
	if (signal == SIGUSR1)
		character |= 1UL << bitcount;
	else if (signal == SIGUSR2)
		character &= ~(1UL << bitcount);
	bitcount += 1;
	if (bitcount > 7)
	{
		context->message[context->msg_pos] = character;
		context->msg_pos += 1;
		bitcount = 0;
	}
}
