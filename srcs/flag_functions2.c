/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_functions2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 11:16:38 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/09 13:38:03 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**	This function will check the length modifier of the flag.
*/

int		get_length_modifier(t_flag *flag, const char *s)
{
	int		i;

	i = 0;
	if (*s == 'l')
	{
		i = 1;
		if (*(s + 1) == 'l')
			i = 2;
		flag->modifier = i;
	}
	else if (*s == 'h')
	{
		i = 1;
		if (*(s + 1) == 'h')
			i = 2;
		flag->modifier = 2 + i;
	}
	return (i);
}

/*
**	This function will check if the character is a flag (1) or not (0).
*/

int		is_flag_character(char c)
{
	if (c == '0' || c == '-' || c == '+' || c == ' ' || c == '#' || c == '\'')
		return (1);
	return (0);
}

/*
**	This function will check if the character is a valid conversion
**	character or not. It will return the 'index' of the conversion character
**	or 0 if invalid.
*/

int		is_conversion_character(char c)
{
	if (c == 'c')
		return (1);
	else if (c == '%')
		return (2);
	else if (c == 's')
		return (3);
	else if (c == 'd' || c == 'i')
		return (4);
	else if (c == 'u')
		return (5);
	else if (c == 'x' || c == 'X')
		return (6);
	else if (c == 'p')
		return (7);
	else if (c == 'f')
		return (8);
	else if (c == 'g')
		return (9);
	else if (c == 'e')
		return (10);
	else if (c == 'n')
		return (11);
	return (0);
}

/*
**	This function will calculate the length in characters of the actual flag.
*/

int		flag_length(const char *s)
{
	int		length;

	length = 1;
	while (*(s + length) != '\0' && !is_conversion_character(*(s + length)))
		length++;
	if (*(s + length) == '\0')
		return (length);
	return (length + 1);
}
