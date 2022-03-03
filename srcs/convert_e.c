/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_e.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 14:49:34 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/27 08:37:56 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>

/*
**	This function will attempt to correct the number before any additional
**	calculations are done.
*/

double			round_to_exponent(double num, int precision)
{
	int			orig_exp;
	long long	int_part;
	size_t		orig_len;

	num = (num < 0) ? -num : num;
	orig_exp = get_exponent(num);
	num = raise_exponent(num, precision);
	int_part = (long long)num;
	orig_len = amount_digits(int_part, 0);
	if (precision == 0 && num - int_part == 0.5 && int_part % 2 == 1)
		int_part++;
	else if (precision == 0 && num - int_part > 0.5)
		int_part++;
	else if (precision != 0 && num - int_part >= 0.5)
		int_part++;
	if (orig_len < amount_digits(int_part, 0))
		orig_exp++;
	num = raise_exponent((double)int_part, orig_exp);
	return (num);
}

/*
**	This function will return the decimal part of the number with the
**	required precision. Round will take either 0 for no rounding, 1 for
**	integer rounding (0 precision) and 2 for normal rounding.
*/

static char		*nums_from_double(double num, int exp,
						int precision, int round)
{
	long long	int_part;
	char		*result;

	num = raise_exponent(num, exp);
	int_part = (long long)num;
	if (round == 1 && num - int_part == 0.5 && int_part % 2 == 1)
		int_part += 1;
	else if (round == 2 && (num - int_part >= 0.5))
		int_part += 1;
	result = ft_ulltoa(int_part, precision, 0);
	return (result);
}

/*
**	This function will take a string in number form and add to it the 'e'
**	and the exponent.
*/

static char		*add_exponent(char *string, double num)
{
	char	*exp_str;
	char	*num_str;
	int		exponent_length;
	int		exponent;

	if (string == NULL)
		return (NULL);
	exponent = get_exponent(num);
	exp_str = malloc(3);
	if (exp_str == NULL)
		return (NULL);
	exp_str[0] = 'e';
	exp_str[1] = (exponent < 0) ? '-' : '+';
	exp_str[2] = '\0';
	exponent = (exponent < 0) ? -exponent : exponent;
	exponent_length = amount_digits(exponent, 0);
	exponent_length = ft_max(2, exponent_length);
	num_str = ft_ulltoa(exponent, exponent_length, 0);
	if (num_str != NULL)
	{
		exp_str = join_and_free(exp_str, num_str);
		if (exp_str != NULL)
			string = join_and_free(string, exp_str);
	}
	return (string);
}

/*
**	This function will take a number and format it in exponential form in
**	ascii.
*/

static char		*format_as_exponent(double num, t_flag *flag)
{
	char		*result;
	char		*dec_part;
	int			exponent;

	exponent = get_exponent(num);
	result = nums_from_double(num, 0, 1, (flag->precision == 0));
	if (result == NULL || (!flag->form && flag->precision == 0) ||
				(flag->remove_trailing_zeroes && fraction_all_zeroes(num)))
		return (result);
	result = join_and_free(result, ft_strdup("."));
	if (result == NULL || flag->precision == 0)
		return (result);
	dec_part = nums_from_double(num, flag->precision, flag->precision, 2);
	if (flag->remove_trailing_zeroes)
		dec_part = trim_zeroes_in_fraction(dec_part);
	if (dec_part == NULL)
		return (NULL);
	result = join_and_free(result, dec_part);
	if (result == NULL)
		return (NULL);
	return (result);
}

/*
**	This function will handle the exponent conversion and print the result.
**	Returns characters printed.
*/

int				convert_e(t_flag *flag, va_list args)
{
	double		number;
	char		*result;
	char		*string;
	int			sign;

	flag->precision = (flag->precision_given) ? flag->precision : 6;
	number = va_arg(args, double);
	sign = (get_dbl_sign(number)) ? '-' : flag->sign;
	if (is_special_case(number))
	{
		string = handle_special_case(number, flag);
		sign = flag->sign;
	}
	else
	{
		number = round_to_exponent(number, flag->precision);
		string = format_as_exponent(number, flag);
		string = add_exponent(string, number);
	}
	if (string == NULL)
		return (0);
	result = format_numeric_string(string, flag, sign, ft_strlen(string));
	if (result == NULL)
		return (0);
	return (print_and_free(result, 0));
}
