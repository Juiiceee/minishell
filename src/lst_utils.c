/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/24 11:58:20 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*ms_lstnew(char **content, t_type data)
{
	t_token	*newlst;

	newlst = malloc(sizeof (*newlst));
	if (!newlst)
		return (NULL);
	newlst->global = content;
	newlst->data_type = data;
	newlst->next = NULL;
	return (newlst);
}

void	ms_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = ms_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

t_token	*ms_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}