/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   client.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/10 14:58:13 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/18 12:14:05 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	*receive_signal_feedback(int signal, siginfo_t *info)
{
	static t_sigfeedback	feedback = (t_sigfeedback){0, false};

	if (info != NULL && info->si_pid == feedback.pid)
	{
		if (info->si_pid == feedback.pid && signal == SIGUSR2)
			feedback.received = true;
	}
	return (&feedback);
}

int	main(int argc, char **argv)
{
	t_sigfeedback		*feedback;
	int32_t				message_length;
	struct sigaction	feedback_usr1;
	struct sigaction	feedback_usr2;

	if (argc != 3)
		mt_error_exit(ERR_STARTUP);
	feedback = receive_signal_feedback(0, NULL);
	feedback_usr1.sa_flags = SA_SIGINFO;
	feedback_usr2.sa_flags = SA_SIGINFO;
	feedback_usr1.__sigaction_u.__sa_sigaction = redirect_received_sig_usr1;
	feedback_usr2.__sigaction_u.__sa_sigaction = redirect_received_sig_usr2;
	mt_atoi(argv[1], &feedback->pid);
	message_length = mt_strlen(argv[2]);
	if (message_length >= ARG_MAX)
		exit(EXIT_FAILURE);
	if (kill(feedback->pid, 0) == -1)
		mt_error_exit(ERR_BAD_PID);
	sigaction(SIGUSR1, &feedback_usr1, NULL);
	sigaction(SIGUSR2, &feedback_usr2, NULL);
	encode_header(feedback->pid, message_length);
	encode_message(feedback->pid, argv[2]);
	while (feedback->received == false)
		usleep(100);
	return (EXIT_SUCCESS);
}
