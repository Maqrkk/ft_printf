/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   format_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 08:59:06 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/18 14:15:05 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libftprintf.h"

/*
**	This function will format the strings for numeric outputs.
*/

char	*format_numeric_string(char *tmp, t_flag *flag, char sign, size_t len)
{
	size_t		width;
	char		*result;
	size_t		i;

	width = ft_max(len + (sign > 0), flag->min_width);
	result = malloc(width + 1);
	if (result == NULL)
	{
		free(tmp);
		return (NULL);
	}
	*(result + width) = '\0';
	fill_string(result, (flag->padding == 1) ? '0' : ' ', 0, width);
	if (sign && flag->padding == 0)
		*(result + width - len - 1) = sign;
	else if (sign)
		*result = sign;
	i = 0;
	if (flag->padding != 2)
		ft_memcpy(result + width - len, tmp, len);
	else
		ft_memcpy(result + (sign > 0), tmp, len);
	free(tmp);
	return (result);
}
