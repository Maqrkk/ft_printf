/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n_times_ten.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 11:52:13 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/10 14:21:12 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

double		ft_n_times_ten(double num, int amount)
{
	while (amount > 0)
	{
		num *= 10;
		amount--;
	}
	return (num);
}
