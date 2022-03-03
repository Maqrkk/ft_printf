/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wstrlen.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/06 14:04:53 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/06 14:33:35 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>

size_t	ft_wstrlen(const wchar_t *s)
{
	size_t		length;

	length = 0;
	while (*s != 0)
	{
		if (*s <= 127)
			length += 1;
		else if (*s <= 2047)
			length += 2;
		else if (*s <= 65535)
			length += 3;
		else
			length += 4;
		s++;
	}
	return (length);
}
