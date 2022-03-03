/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_n_divided_by_ten.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 11:50:52 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/24 09:43:06 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

long long	ft_n_divided_by_ten(long long num, int amount)
{
	while (amount > 0)
	{
		num /= 10;
		amount--;
	}
	return (num);
}
