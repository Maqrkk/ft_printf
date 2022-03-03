/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exponent_functions.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/23 10:19:50 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/23 13:43:03 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

/*
**	This function will return the exponent of the number.
*/

int		get_exponent(double num)
{
	int		exponent;

	exponent = 0;
	if (get_dbl_exp(num == 0) && get_dbl_man(num) == 0)
		return (0);
	while ((long long)num >= 10 || (long long)num <= -10)
	{
		num /= 10;
		exponent++;
	}
	while ((long long)num == 0)
	{
		num *= 10;
		exponent--;
	}
	return (exponent);
}

/*
**	This function will raise a number to an exponent.
*/

double	raise_exponent(double num, int exponent)
{
	int		exponent_offset;

	exponent_offset = -get_exponent(num) + exponent;
	while (exponent_offset != 0)
	{
		if (exponent_offset > 0)
		{
			num *= 10;
			exponent_offset--;
		}
		else
		{
			num /= 10;
			exponent_offset++;
		}
	}
	return (num);
}

/*
**	This function will check if a fraction is all zeroes.
*/

int		fraction_all_zeroes(double num)
{
	num = raise_exponent(num, 0);
	num -= (long long)num;
	if (num == 0)
		return (1);
	return (0);
}
