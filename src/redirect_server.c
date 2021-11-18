/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect_server.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 22:05:47 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/15 16:22:58 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	redirect_decode_header_usr1(int signal, siginfo_t *info, void *context)
{
	(void)context;
	decode_header(signal, info);
}

void	redirect_decode_header_usr2(int signal, siginfo_t *info, void *context)
{
	(void)context;
	decode_header(signal, info);
}

void	redirect_decode_signal_usr1(int signal, siginfo_t *info, void *context)
{
	(void)context;
	decode_signal(signal, info);
}

void	redirect_decode_signal_usr2(int signal, siginfo_t *info, void *context)
{
	(void)context;
	decode_signal(signal, info);
}
