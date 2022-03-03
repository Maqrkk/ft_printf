/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_x.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 11:37:32 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/17 08:22:30 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>

/*
**	This function will cast the number to the corresponding modifier.
*/

static void	cast_arg(unsigned long long *number, int modifier)
{
	if (modifier == 0)
		*number = (unsigned long long)(unsigned int)*number;
	if (modifier == 1)
		*number = (unsigned long long)(unsigned long)*number;
	if (modifier == 3)
		*number = (unsigned long long)(unsigned short)*number;
	if (modifier == 4)
		*number = (unsigned long long)(unsigned char)*number;
}

/*
**	This function will handle the unsigned hexadecimal conversion, and print
**	the result.
**	Returns characters printed.
*/

int			convert_x(t_flag *flag, va_list args)
{
	unsigned long long	number;
	char				*result;
	char				*string;
	int					length;

	if (flag->precision_given && flag->padding == 1)
		flag->padding = 0;
	number = va_arg(args, unsigned long long);
	cast_arg(&number, flag->modifier);
	length = amount_digits_hex(number);
	if (flag->precision_given && flag->precision == 0 && number == 0)
		length = 0;
	length = ft_max(length, flag->precision);
	length += 2 * (flag->form && number);
	if (flag->padding == 1)
		length = ft_max(length, flag->min_width);
	string = ft_itoa_base(number, 16, length, (flag->conversion == 'X'));
	if (flag->form && number)
		*(string + 1) = flag->conversion;
	result = format_numeric_string(string, flag, 0, ft_strlen(string));
	return (print_and_free(result, 0));
}
