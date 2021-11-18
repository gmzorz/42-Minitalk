/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 14:04:59 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/17 14:07:31 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	mt_putchar(char c)
{
	write(1, &c, 1);
}

void	mt_putstr(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	mt_putnbr(int n)
{
	if (n < 0)
	{
		mt_putchar('-');
		if (n == -2147483648)
		{
			mt_putnbr(214748364);
			mt_putchar('8');
			return ;
		}
		n = -n;
	}
	if (n > 9)
		mt_putnbr(n / 10);
	mt_putchar((n % 10) + '0');
}
