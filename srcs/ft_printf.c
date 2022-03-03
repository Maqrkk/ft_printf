/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 14:14:06 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/27 08:06:41 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include "libftprintf.h"
#include <unistd.h>

/*
** This function will mostly divide all the tasks to helper functions.
*/

int			ft_printf(const char *format, ...)
{
	va_list		args;
	t_flag		*flag;
	int			printed;

	printed = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
		{
			flag = create_flag(format, args);
			if (flag->conversion == 0)
				return (print_error(flag, args));
			printed += print_conversion(flag, args, printed);
			free(flag);
			format += flag_length(format);
		}
		else
		{
			printed += print_text(format);
			format += length_to_flag(format);
		}
	}
	va_end(args);
	return (printed);
}

/*
**	This function will read how many characters are 'plain text' and should
**	be printed normally.
*/

int			length_to_flag(const char *s)
{
	int		i;

	i = 0;
	while (*(s + i) != '\0' && *(s + i) != '%')
		i++;
	return (i);
}

/*
**	This function will print the plain text to the screen.
*/

int			print_text(const char *s)
{
	int			length;

	length = length_to_flag(s);
	write(1, s, length);
	return (length);
}

/*
**	This function will do the conversion and print it to the screen.
*/

int			print_conversion(t_flag *flag, va_list args, int printed)
{
	if (flag->conversion == 'c' || flag->conversion == '%')
		return (convert_c(flag, args));
	else if (flag->conversion == 's')
		return (convert_s(flag, args));
	else if (flag->conversion == 'i' || flag->conversion == 'd')
		return (convert_i(flag, args));
	else if (flag->conversion == 'u')
		return (convert_u(flag, args));
	else if (flag->conversion == 'x' || flag->conversion == 'X')
		return (convert_x(flag, args));
	else if (flag->conversion == 'p')
		return (convert_p(flag, args));
	else if (flag->conversion == 'f')
		return (convert_f(flag, args));
	else if (flag->conversion == 'n')
		return (convert_n(flag, args, printed));
	else if (flag->conversion == 'e')
		return (convert_e(flag, args));
	else if (flag->conversion == 'g')
		return (convert_g(flag, args));
	return (0);
}

/*
**	This function will print an error message in case of an incomplete flag.
*/

int			print_error(t_flag *flag, va_list args)
{
	free(flag);
	va_end(args);
	write(1, "Error in format string.", 23);
	return (-1);
}
