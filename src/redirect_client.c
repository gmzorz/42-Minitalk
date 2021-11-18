/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_client.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 14:05:41 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/16 12:46:43 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	redirect_received_sig_usr1(int signal, siginfo_t *info, void *context)
{
	(void)context;
	receive_signal_feedback(signal, info);
}

void	redirect_received_sig_usr2(int signal, siginfo_t *info, void *context)
{
	(void)context;
	receive_signal_feedback(signal, info);
}
