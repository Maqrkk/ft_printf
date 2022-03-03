/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 13:12:13 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/29 12:29:34 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char		num_to_char(unsigned int n, int capital)
{
	if (n > 15)
		return (0);
	if (n < 10)
		return (n + '0');
	if (n == 10)
		return ('a' - capital * 32);
	if (n == 11)
		return ('b' - capital * 32);
	if (n == 12)
		return ('c' - capital * 32);
	if (n == 13)
		return ('d' - capital * 32);
	if (n == 14)
		return ('e' - capital * 32);
	return ('f' - capital * 32);
}

char			*ft_itoa_base(unsigned long long n, unsigned char base,
		int length, int capital)
{
	char	*result;
	int		i;

	if (base == 0 || base > 16)
		return (NULL);
	result = malloc(length + 1);
	if (result == NULL)
		return (NULL);
	i = length - 1;
	*(result + length) = '\0';
	while (i >= 0)
	{
		*(result + i) = num_to_char(n % base, capital);
		n /= base;
		i--;
	}
	return (result);
}
