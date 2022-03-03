/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   float_functions.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/11 14:04:17 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/17 08:16:44 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**	This function returns the sign of a double.
*/

int					get_dbl_sign(double num)
{
	unsigned long long	ullnum;

	ullnum = *((unsigned long long*)&num);
	return (ullnum >> 63);
}

/*
**	This function returns the exponent of a double.
*/

int					get_dbl_exp(double num)
{
	unsigned long long	ullnum;
	unsigned long long	exponent_mask;

	exponent_mask = 0x7FF0000000000000;
	ullnum = *((unsigned long long*)&num);
	return ((exponent_mask & ullnum) >> 52);
}

/*
**	This function returns the mantissa of a double as an unsigned long long.
*/

unsigned long long	get_dbl_man(double num)
{
	unsigned long long	ullnum;
	unsigned long long	mantissa_mask;

	mantissa_mask = 0x000FFFFFFFFFFFFF;
	ullnum = *((unsigned long long*)&num);
	return (mantissa_mask & ullnum);
}

/*
**	This function will check if the double is a special case like infinity
**	or NaN.
*/

int					is_special_case(double num)
{
	int		exponent;

	exponent = get_dbl_exp(num);
	if (exponent == 2047)
		return (1);
	return (0);
}

/*
**	This function will handle the nan and inf special cases.
*/

char				*handle_special_case(double num, t_flag *flag)
{
	char	*result;

	if (get_dbl_man(num) == 0)
	{
		result = ft_strdup("inf");
		if (get_dbl_sign(num))
			flag->sign = '-';
	}
	else
	{
		result = ft_strdup("nan");
		flag->sign = 0;
	}
	if (flag->padding == 1)
		flag->padding = 0;
	return (result);
}
