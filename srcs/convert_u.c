/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_u.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/28 09:37:55 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/23 08:31:57 by mpeerdem      ########   odam.nl         */
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
**	This function will handle the unsigned decimal conversion, and print
**	the result.
**	Returns characters printed.
*/

int			convert_u(t_flag *flag, va_list args)
{
	unsigned long long	number;
	char				*result;
	char				*string;
	int					length;

	if (flag->precision_given && flag->padding == 1)
		flag->padding = 0;
	number = va_arg(args, unsigned long long);
	cast_arg(&number, flag->modifier);
	length = ft_max(amount_udigits(number, flag->grouping), flag->precision);
	if (flag->precision_given && flag->precision == 0 && number == 0)
		length = 0;
	string = ft_ulltoa(number, length, flag->grouping);
	result = format_numeric_string(string, flag, 0, ft_strlen(string));
	return (print_and_free(result, 0));
}
