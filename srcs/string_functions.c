/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/25 10:51:26 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/23 08:32:03 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <wchar.h>
#include "libftprintf.h"

/*
**	This helper function will simply put the c character length amount of
**	times into the string, starting from index start.
*/

void		fill_string(char *string, char c, int start, int length)
{
	int		i;

	i = 0;
	while (i < length)
	{
		*(string + start + i) = c;
		i++;
	}
}

/*
**	This function will return the amount of digits (in base 10) that the
**	number has in ascii, excluding the negative sign.
*/

size_t		amount_digits(long long num, int grouping_mode)
{
	size_t	length;

	if (num == 0)
		return (1);
	length = 0;
	while (num != 0)
	{
		num /= 10;
		length++;
	}
	if (grouping_mode == 1)
		length += (length - 1) / 3;
	return (length);
}

/*
**	This function will return the amount of digits in base 10 that the has in
**	ascii, for unsigned numbers.
*/

size_t		amount_udigits(unsigned long long num, int grouping_mode)
{
	size_t	length;

	if (num == 0)
		return (1);
	length = 0;
	while (num != 0)
	{
		num /= 10;
		length++;
	}
	if (grouping_mode == 1)
		length += (length - 1) / 3;
	return (length);
}

/*
**	This function will return the amount of characters for a hexadecimal.
*/

size_t		amount_digits_hex(unsigned long long num)
{
	size_t	length;

	if (num == 0)
		return (1);
	length = 0;
	while (num != 0)
	{
		num /= 16;
		length++;
	}
	return (length);
}

/*
**	This function will concatenate two strings and free them.
*/

char		*join_and_free(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (result == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strlcpy(result, s1, len1 + len2 + 1);
	i = 0;
	while (i < len2)
	{
		*(result + len1 + i) = *(s2 + i);
		i++;
	}
	*(result + len1 + i) = '\0';
	free(s1);
	free(s2);
	return (result);
}
