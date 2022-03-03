/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_g.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/13 11:09:24 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/24 08:04:58 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdarg.h>

int			convert_g(t_flag *flag, va_list args)
{
	double		number;
	int			exponent;
	va_list		arg_cpy;

	flag->precision = (flag->precision_given) ? flag->precision : 6;
	flag->precision_given = 1;
	flag->precision = (flag->precision == 0) ? 1 : flag->precision;
	va_copy(arg_cpy, args);
	number = va_arg(arg_cpy, double);
	va_end(arg_cpy);
	if (is_special_case(number))
		return (convert_f(flag, args));
	exponent = get_exponent(number);
	if (!flag->form)
		flag->remove_trailing_zeroes = 1;
	if (flag->precision > exponent && exponent >= -4)
	{
		flag->precision -= (exponent + 1);
		return (convert_f(flag, args));
	}
	flag->precision -= 1;
	return (convert_e(flag, args));
}
