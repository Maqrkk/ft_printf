/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 10:03:02 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/12/16 10:10:46 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*item;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	item = *alst;
	while (item->next)
		item = item->next;
	item->next = new;
}
