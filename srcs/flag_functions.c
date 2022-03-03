/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flag_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/18 13:15:15 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/17 08:16:33 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>

/*
**	This function will call all helper functions to make the flag.
*/

t_flag		*create_flag(const char *format, va_list args)
{
	t_flag	*flag;

	format++;
	flag = create_empty_flag();
	if (is_flag_character(*format))
		format += get_flags(flag, format);
	if (ft_isdigit(*format) || *format == '*')
		format += get_width(flag, format, args);
	if (*format == '.')
		format += get_precision(flag, format, args);
	if (*format == 'l' || *format == 'h')
		format += get_length_modifier(flag, format);
	if (is_conversion_character(*format))
		flag->conversion = *format;
	return (flag);
}

/*
**	This function will create an empty flag struct.
*/

t_flag		*create_empty_flag(void)
{
	t_flag	*flag;

	flag = malloc(sizeof(t_flag));
	if (flag == NULL)
		return (NULL);
	flag->form = 0;
	flag->padding = 0;
	flag->sign = 0;
	flag->grouping = 0;
	flag->min_width = 0;
	flag->precision = 0;
	flag->precision_given = 0;
	flag->modifier = 0;
	flag->conversion = 0;
	flag->remove_trailing_zeroes = 0;
	return (flag);
}

/*
**	This function will parse the 0, -, +,  , and # flags at the start.
*/

int			get_flags(t_flag *flag, const char *s)
{
	int		i;

	i = 0;
	while (is_flag_character(*(s + i)))
	{
		if (*(s + i) == ' ' && flag->sign != '+')
			flag->sign = ' ';
		if (*(s + i) == '+')
			flag->sign = '+';
		if (*(s + i) == '#')
			flag->form = 1;
		if (*(s + i) == '0' && flag->padding != 2)
			flag->padding = 1;
		if (*(s + i) == '-')
			flag->padding = 2;
		if (*(s + i) == '\'')
			flag->grouping = 1;
		i++;
	}
	return (i);
}

/*
**	This function will calculate the minimum field width.
*/

int			get_width(t_flag *flag, const char *s, va_list args)
{
	int		i;
	int		width;

	if (*s == '*')
	{
		width = va_arg(args, int);
		if (width < 0)
		{
			width *= -1;
			flag->padding = 2;
		}
		flag->min_width = width;
		return (1);
	}
	i = 0;
	width = 0;
	while (*(s + i) >= '0' && *(s + i) <= '9')
	{
		width = (width * 10) + (*(s + i) - '0');
		i++;
	}
	flag->min_width = width;
	return (i);
}

/*
**	This function calculates the precision for a flag.
*/

int			get_precision(t_flag *flag, const char *s, va_list args)
{
	int		i;
	int		precision;

	flag->precision_given = 1;
	if (*(s + 1) == '*')
	{
		flag->precision = va_arg(args, int);
		if (flag->precision < 0)
		{
			flag->precision_given = 0;
			flag->precision = 0;
		}
		return (2);
	}
	i = 1;
	precision = 0;
	while (*(s + i) >= '0' && *(s + i) <= '9')
	{
		precision = (precision * 10) + (*(s + i) - '0');
		i++;
	}
	flag->precision = precision;
	return (i);
}
