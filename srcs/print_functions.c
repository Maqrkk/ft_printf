/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 13:29:52 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/18 15:08:08 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include "libftprintf.h"

/*
**	This function will print a string, free it, and return the amount of
**	characters printed.
**	If amount is 0, the strlen is used, otherwise use amount.
*/

int			print_and_free(char *string, int amount)
{
	if (string == NULL)
		return (0);
	if (amount == 0)
		amount = ft_strlen(string);
	write(1, string, amount);
	free(string);
	return (amount);
}

/*
**	This function will print a wide string, free it, and return the amount
**	of bytes printed.
*/

int			wprint_and_free(wchar_t *string, int amount)
{
	unsigned char	*utf8_string;
	int				size_in_bytes;

	if (amount == 0)
		while (*(string + amount) != '\0')
			amount++;
	size_in_bytes = count_bytes(string, amount);
	utf8_string = malloc(size_in_bytes);
	wchar_to_utf8_string(utf8_string, string, size_in_bytes);
	write(1, utf8_string, size_in_bytes);
	free(string);
	free(utf8_string);
	return (size_in_bytes);
}

/*
**	This function will build up the first argument from the second,
**	converting each character to UTF-8 in the process.
*/

void		wchar_to_utf8_string(unsigned char *result, wchar_t *src,
				int amount)
{
	int		i;
	int		size;

	if (result == NULL)
		return ;
	i = 0;
	size = 0;
	while (size + ft_wcbytelen(*(src + i)) <= amount)
	{
		result += single_wchar_to_utf8(result, *(src + i));
		size += ft_wcbytelen(*(src + i));
		i++;
	}
	*result = '\0';
}

/*
**	This function converts a single wchar into the UTF-8 representation.
**	It returns the amount of bytes written.
*/

int			single_wchar_to_utf8(unsigned char *result, wchar_t src)
{
	if (src <= 127)
	{
		*result = src;
		return (1);
	}
	else if (src <= 2047)
	{
		*result = 0xC0 | (src >> 6);
		*(result + 1) = 0x80 | (src & 0x3F);
		return (2);
	}
	else if (src <= 65535)
	{
		*result = 0xE0 | (src >> 12);
		*(result + 1) = 0x80 | ((src >> 6) & 0x3F);
		*(result + 2) = 0x80 | (src & 0x3F);
		return (3);
	}
	*result = 0xF0 | (src >> 18);
	*(result + 1) = 0x80 | ((src >> 12) & 0x3F);
	*(result + 2) = 0x80 | ((src >> 6) & 0x3F);
	*(result + 3) = 0x80 | (src & 0x3F);
	return (4);
}

/*
**	This function counts the amount of bytes necessary to print the first
**	'amount' of characters in a wide string.
*/

int			count_bytes(wchar_t *string, int amount)
{
	int		i;
	int		bytes;

	i = 0;
	bytes = 0;
	while (i < amount)
	{
		if (*(string + i) <= 127)
			bytes += 1;
		else if (*(string + i) <= 2047)
			bytes += 2;
		else if (*(string + i) <= 65535)
			bytes += 3;
		else
			bytes += 4;
		i++;
	}
	return (bytes);
}
