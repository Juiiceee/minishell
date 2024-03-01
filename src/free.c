/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:30:29 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/01 15:17:45 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	freelst(t_list *lst)
{
	t_list *tmp;

	while (lst)
	{
		free(lst->content);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void free_list_element(t_list **lst, t_list *element)
{
	t_list	*prev;
	if (!*lst || !element)
		return;
	if (*lst == element)
	{
		*lst = element->next;
		free(element);
		return;
	}
	prev = *lst;
	while (prev->next && prev->next != element)
		prev = prev->next;
	if (prev->next == element)
	{
		prev->next = element->next;
		free(element);
	}
}
