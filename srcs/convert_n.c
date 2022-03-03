/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   convert_n.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/04 13:26:02 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/18 14:45:24 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdarg.h>

/*
**	This function will handle l and ll for n conversion.
*/

static void		long_pointers(int modifier, va_list args, int printed)
{
	long		*lpointer;
	long long	*llpointer;

	if (modifier == 1)
	{
		lpointer = va_arg(args, long*);
		if (lpointer == NULL)
			return ;
		*lpointer = printed;
	}
	else if (modifier == 2)
	{
		llpointer = va_arg(args, long long*);
		if (llpointer == NULL)
			return ;
		*llpointer = printed;
	}
}

/*
**	This function will handle h and hh for n conversion.
*/

static void		short_pointers(int modifier, va_list args, int printed)
{
	signed char	*hhpointer;
	short		*hpointer;

	if (modifier == 3)
	{
		hpointer = va_arg(args, short*);
		if (hpointer == NULL)
			return ;
		*hpointer = printed;
	}
	else if (modifier == 4)
	{
		hhpointer = va_arg(args, signed char*);
		if (hhpointer == NULL)
			return ;
		*hhpointer = printed;
	}
}

/*
**	This function will handle the n conversion.
*/

int				convert_n(t_flag *flag, va_list args, int printed)
{
	int			*pointer;

	if (flag->modifier == 0)
	{
		pointer = va_arg(args, int*);
		if (pointer == NULL)
			return (0);
		*pointer = printed;
	}
	else if (flag->modifier == 1 || flag->modifier == 2)
		long_pointers(flag->modifier, args, printed);
	else if (flag->modifier == 3 || flag->modifier == 4)
		short_pointers(flag->modifier, args, printed);
	return (0);
}
