/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/11 22:27:55 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/17 14:21:09 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	mt_error_exit(const char *message)
{
	mt_putstr(ERRMSG);
	mt_putstr(message);
	mt_putstr("\n");
	exit(EXIT_FAILURE);
}

bool	mt_error(const char *message)
{
	mt_putstr(ERRMSG);
	mt_putstr(message);
	mt_putstr("\n");
	return (false);
}

bool	mt_error_free(const char *message, void *object)
{
	if (object)
		free(object);
	if (message)
		return (mt_error(message));
	return (false);
}
