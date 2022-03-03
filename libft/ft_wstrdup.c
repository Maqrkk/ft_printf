/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_wstrdup.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 13:25:53 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/17 16:14:39 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <wchar.h>
#include <stdlib.h>

wchar_t		*ft_wstrdup(wchar_t *source)
{
	int			i;
	wchar_t		*result;

	if (source == NULL)
		return (ft_wstrdup(L"(null)"));
	i = 0;
	while (*(source + i) != '\0')
		i++;
	result = malloc(sizeof(wchar_t) * (i + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*(source + i) != '\0')
	{
		*(result + i) = *(source + i);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}
