/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wcbytelen.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 09:17:22 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/09 09:19:53 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>

int		ft_wcbytelen(wchar_t c)
{
	if (c <= 127)
		return (1);
	else if (c <= 2047)
		return (2);
	else if (c <= 65535)
		return (3);
	return (4);
}
