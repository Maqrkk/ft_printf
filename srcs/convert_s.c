/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_s.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/22 14:51:29 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/18 13:26:35 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>
#include <stdarg.h>
#include <wchar.h>

/*
**	This function will convert a normal char string to a wchar string.
*/

static wchar_t	*char_to_wide_string(char *src)
{
	wchar_t		*result;
	size_t		strsize;
	size_t		i;
	char		*string;

	string = (src == NULL) ? ft_strdup("(null)") : ft_strdup(src);
	strsize = ft_strlen(string);
	result = malloc(sizeof(wchar_t) * (strsize + 1));
	if (result == NULL)
	{
		free(string);
		return (NULL);
	}
	i = 0;
	while (i < strsize)
	{
		*(result + i) = *(string + i);
		i++;
	}
	*(result + i) = '\0';
	free(string);
	return (result);
}

/*
**	Calculates the right size for a wide string based on precision and the
**	string itseslf.
*/

static size_t	get_length(t_flag *flag, wchar_t *str)
{
	size_t	length;
	int		i;
	size_t	precision;

	if (!flag->precision_given)
		return (ft_wstrlen(str));
	precision = flag->precision;
	i = 0;
	length = 0;
	while (*(str + i) != '\0' && length + ft_wcbytelen(*(str + i)) <= precision)
	{
		length += ft_wcbytelen(*(str + i));
		i++;
	}
	return (length);
}

/*
**	This function will handle the creation of the result string.
*/

static void		create_string(char *result, unsigned char *string,
					t_flag *flag, size_t length)
{
	wchar_t	fill;
	int		start;
	size_t	i;
	size_t	width;

	width = ft_max(length, flag->min_width);
	fill = (flag->padding == 1) ? '0' : ' ';
	fill_string(result, fill, 0, width);
	start = (flag->padding == 2) ? 0 : width - length;
	i = 0;
	while (i < length)
	{
		*(result + start + i) = *(string + i);
		i++;
	}
	free(string);
}

/*
**	This function will handle the string conversion, and print the result.
**	Returns characters printed.
*/

int				convert_s(t_flag *flag, va_list args)
{
	wchar_t			*str;
	unsigned char	*tmp;
	char			*result;
	size_t			width;
	size_t			length;

	if (flag->modifier == 1)
		str = ft_wstrdup(va_arg(args, wchar_t*));
	else
		str = char_to_wide_string(va_arg(args, char*));
	if (str == NULL)
		return (0);
	length = get_length(flag, str);
	tmp = malloc(length + 1);
	wchar_to_utf8_string(tmp, str, length);
	free(str);
	width = ft_max(length, flag->min_width);
	result = malloc(width + 1);
	if (result == NULL)
		return (0);
	*(result + width) = '\0';
	create_string(result, tmp, flag, length);
	return (print_and_free(result, 0));
}
