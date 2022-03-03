/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_i.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/27 09:22:19 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/23 08:42:02 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>

/*
**	This function will cast the number to the corresponding modifier.
*/

static void	cast_arg(long long *number, int modifier)
{
	if (modifier == 0)
		*number = (long long)(int)*number;
	if (modifier == 1)
		*number = (long long)(long)*number;
	if (modifier == 3)
		*number = (long long)(short)*number;
	if (modifier == 4)
		*number = (long long)(signed char)*number;
}

/*
**	This function will handle the integer conversion, and print the result.
**	Returns characters printed.
*/

int			convert_i(t_flag *flag, va_list args)
{
	long long	number;
	char		*result;
	char		*string;
	int			sign;
	int			length;

	if (flag->precision_given && flag->padding == 1)
		flag->padding = 0;
	number = va_arg(args, long long);
	cast_arg(&number, flag->modifier);
	sign = (number < 0) ? '-' : flag->sign;
	length = ft_max(amount_digits(number, flag->grouping), flag->precision);
	if (flag->precision_given && flag->precision == 0 && number == 0)
		length = 0;
	string = ft_lltoa(number, length, flag->grouping);
	result = format_numeric_string(string, flag, sign, ft_strlen(string));
	return (print_and_free(result, 0));
}
