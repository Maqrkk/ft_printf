/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ulltoa.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 14:03:52 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/23 08:35:46 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	absint(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

static void	fill_string_backwards(char *string, unsigned long long num,
		int dots, int length)
{
	int		pos;

	pos = 1;
	while (length >= 0)
	{
		if (dots > 0 && pos % 4 == 0)
		{
			*(string + length) = ',';
			dots--;
		}
		else
		{
			*(string + length) = absint(num % 10) + '0';
			num /= 10;
		}
		length--;
		pos++;
	}
}

char		*ft_ulltoa(unsigned long long num, int length, int grouping_mode)
{
	char	*result;
	int		dots;

	dots = (grouping_mode) ? (ft_intlen(num) - 1) / 3 : 0;
	result = malloc(length + 1 + dots);
	if (result == NULL)
		return (NULL);
	*(result + length) = '\0';
	fill_string_backwards(result, num, dots, length - 1);
	return (result);
}
