/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 09:24:29 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/18 16:30:45 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>

/*
**	This function will handle the actual filling of the string.
*/

static void	fill_cstring(wchar_t *string, wchar_t c, char mode, int width)
{
	int		i;

	i = 0;
	while (i < width)
	{
		if (i == 0 && mode == 2)
			*string = c;
		else if (mode == 2)
			*(string + i) = ' ';
		else if (i != width - 1)
			*(string + i) = (mode == 0) ? ' ' : '0';
		else
			*(string + i) = c;
		i++;
	}
}

/*
**	This function will handle normal characters.
*/

static int	convert_c_normal(t_flag *flag, va_list args)
{
	char	c;
	char	*result;
	int		width;

	c = va_arg(args, int);
	width = ft_max(flag->min_width, 1);
	result = malloc(width + 1);
	if (result == NULL)
		return (0);
	*(result + width) = '\0';
	fill_string(result, (flag->padding == 1) ? '0' : ' ', 0, width);
	if (flag->padding == 2)
		*result = c;
	else
		*(result + width - 1) = c;
	return (print_and_free(result, width));
}

/*
**	This function will handle the character conversion, and print the result.
**	Returns characters printed.
*/

int			convert_c(t_flag *flag, va_list args)
{
	wchar_t		c;
	char		mode;
	wchar_t		*result;
	int			width;
	int			clen;

	mode = flag->padding;
	if (flag->conversion == '%')
		c = '%';
	else if (flag->modifier == 1)
		c = (wchar_t)va_arg(args, wint_t);
	else
		return (convert_c_normal(flag, args));
	clen = ft_wcbytelen(c);
	width = ft_max((int)flag->min_width - (clen - 1), 1);
	result = malloc(sizeof(wchar_t) * (width + 1));
	if (result == NULL)
		return (0);
	*(result + width) = '\0';
	fill_cstring(result, c, mode, width);
	return (wprint_and_free(result, width));
}
