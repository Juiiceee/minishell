/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:30:29 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/02 14:17:19 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freelst(t_list *lst)
{
	t_list	*tmp;

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

void	free_list_element(t_list **lst, t_list *element)
{
	t_list	*prev;

	if (!*lst || !element)
		return ;
	if (*lst == element)
	{
		*lst = element->next;
		free(element->content);
		free(element);
		return ;
	}
	prev = *lst;
	while (prev->next && prev->next != element)
		prev = prev->next;
	if (prev->next == element)
	{
		prev->next = element->next;
		free(element->content);
		free(element);
	}
}
