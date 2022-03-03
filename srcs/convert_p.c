/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_p.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/29 09:35:00 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/17 08:23:09 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdarg.h>

/*
**	This function will handle the pointer conversion, and print the result.
**	Returns characters printed.
*/

int			convert_p(t_flag *flag, va_list args)
{
	unsigned long long	number;
	char				*result;
	char				*string;
	size_t				length;

	number = (unsigned long long)va_arg(args, void*);
	length = amount_digits_hex(number) + 2;
	if (flag->padding == 1 && flag->min_width > length)
		length = flag->min_width;
	string = ft_itoa_base(number, 16, length, 0);
	*(string + 1) = 'x';
	result = format_numeric_string(string, flag, 0, ft_strlen(string));
	return (print_and_free(result, 0));
}
