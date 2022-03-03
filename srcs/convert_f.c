/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_f.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 11:09:07 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/24 11:43:44 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>

/*
**	This function will get the 'int' part of a float, rounding when necessary.
*/

static long long	get_int_part(double num, int precision)
{
	unsigned long long	result;

	result = (long long)num;
	if (precision == 0)
	{
		if (num - result == 0.5 && result % 2 == 1)
			return (result + 1);
		if (num - result > 0.5)
			return (result + 1);
		return (result);
	}
	num = ft_n_times_ten(num, precision);
	result = ft_n_divided_by_ten((long long)(num + 0.5), precision);
	return (result);
}

/*
**	This function will take a number and format it as a float in ascii
**	form, according to the precision.
*/

static char			*format_as_float(double num, t_flag *flag)
{
	long long	int_part;
	double		tmp_num;
	char		*result;
	char		*tmp_str;

	num = (num < 0) ? num * -1 : num;
	int_part = get_int_part(num, flag->precision);
	tmp_num = ft_n_times_ten(num - (long long)num, flag->precision);
	result = ft_ulltoa(int_part, amount_digits(int_part, flag->grouping),
			flag->grouping);
	if (result == NULL)
		return (NULL);
	if (!flag->form && flag->precision == 0)
		return (result);
	result = join_and_free(result, ft_strdup("."));
	if (flag->form && flag->precision == 0)
		return (result);
	tmp_str = ft_ulltoa((long long)(tmp_num + 0.5), flag->precision, 0);
	if (tmp_str == NULL)
		return (NULL);
	result = join_and_free(result, tmp_str);
	if (flag->remove_trailing_zeroes)
		result = trim_zeroes_in_fraction(result);
	return (result);
}

/*
**	This function will handle the float conversion, and print the result.
**	Returns characters printed.
*/

int					convert_f(t_flag *flag, va_list args)
{
	double			number;
	char			*result;
	char			*string;
	int				sign;

	flag->precision = (flag->precision_given) ? flag->precision : 6;
	number = va_arg(args, double);
	if (is_special_case(number))
	{
		string = handle_special_case(number, flag);
		sign = flag->sign;
	}
	else
	{
		string = format_as_float(number, flag);
		sign = (get_dbl_sign(number)) ? '-' : flag->sign;
	}
	if (string == NULL)
		return (0);
	result = format_numeric_string(string, flag, sign, ft_strlen(string));
	if (result == NULL)
		return (0);
	return (print_and_free(result, 0));
}

/*
**	This function returns the original string with the trailing zeroes
**	removed.
*/

char				*trim_zeroes_in_fraction(char *source)
{
	char	*result;
	int		size;

	if (source == NULL)
		return (NULL);
	size = ft_strlen(source);
	while (*(source + (size - 1)) == '0')
		size--;
	if (*(source + (size - 1)) == '.')
		size--;
	result = malloc(size + 1);
	if (result == NULL)
	{
		free(source);
		return (NULL);
	}
	result = ft_memcpy(result, source, size);
	*(result + size) = '\0';
	free(source);
	return (result);
}
