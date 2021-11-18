/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <goosterl@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/17 13:38:15 by goosterl      #+#    #+#                 */
/*   Updated: 2021/11/17 14:06:23 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*mt_memset(void *b, int c, size_t len)
{
	unsigned char	*m;
	size_t			i;

	i = 0;
	m = (unsigned char *)b;
	while (i < len)
	{
		m[i] = c;
		i++;
	}
	return (b);
}

int	mt_atoi(char *str, int *num)
{
	int		index;
	long	ret;

	index = 0;
	ret = 0;
	if (!str)
		return (0);
	if (!num)
		return (-1);
	if (str[index] == '-')
		index++;
	while (str[index] && (str[index] >= '0' && str[index] <= '9'))
	{
		ret = 10 * ret + (str[index] - '0');
		index++;
	}
	if (index == 0 || (str[0] == '-' && index == 1))
		return (0);
	if (str[0] == '-')
		*num = -ret;
	else
		*num = ret;
	return (index);
}

size_t	mt_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
