/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 13:06:42 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void init_new_null(t_exec *new)
{
	new->builtin = 0;
	new->cmd = NULL;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
}

t_exec	*exe_lstnew(t_token *tmp)
{
	t_exec	*newlst;

	printf("%s", tmp->global[0]);
	newlst = malloc(sizeof (*newlst));
	init_new_null(newlst);
	if (!newlst)
		return (NULL);
	while (tmp && tmp->data_type != PIPE)
	{
		if (tmp->data_type == CMD)
			newlst->cmd = tmp->global;
		if (tmp->data_type == IN_REDIRECT)
			newlst->in = tmp->global;
		if (tmp->data_type == OU_REDIRECT)
			newlst->out = tmp->global;
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	return (newlst);
}

void	exe_lstadd_back(t_exec **lst, t_exec *new)
{
	t_exec	*last;

	last = exe_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

t_exec	*exe_lstlast(t_exec *lst)
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
