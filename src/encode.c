/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   encode.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/12 14:08:35 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/18 12:07:03 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	encode_header(const int32_t pid, const int32_t header)
{
	SIGNAL_USR	signal;		
	int32_t		bit_pos;
	int32_t		current_bit;

	bit_pos = 0;
	while (bit_pos < 32)
	{
		current_bit = ((header >> bit_pos) & 1);
		if (current_bit)
			signal = SIGUSR1;
		else
			signal = SIGUSR2;
		if (kill(pid, signal) == -1)
			exit(EXIT_FAILURE);
		pause();
		usleep(100);
		bit_pos += 1;
	}
}

void	encode_message(const int32_t pid, const char *message)
{
	SIGNAL_USR	signal;
	int32_t		char_pos;
	int32_t		bit_pos;
	int32_t		current_bit;

	char_pos = 0;
	while (message[char_pos] != '\0')
	{
		bit_pos = 0;
		while (bit_pos < 8)
		{
			current_bit = ((message[char_pos] >> bit_pos) & 1);
			if (current_bit)
				signal = SIGUSR1;
			else
				signal = SIGUSR2;
			if (kill(pid, signal) == -1)
				exit(EXIT_FAILURE);
			pause();
			usleep(100);
			bit_pos += 1;
		}
		char_pos += 1;
	}
}
