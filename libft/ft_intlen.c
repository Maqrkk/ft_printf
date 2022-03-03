/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 13:27:57 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/09 13:30:08 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int		ft_intlen(long long num)
{
	int		length;

	length = 0;
	while (num != 0)
	{
		num /= 10;
		length += 1;
	}
	return (length);
}
