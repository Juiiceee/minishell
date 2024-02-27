/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 12:19:34 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*tok_lstnew(char **content, t_type data)
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

void	tok_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*last;

	last = tok_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

t_token	*tok_lstlast(t_token *lst)
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

int is_splitted(char *tmp)
{
	int i;

	i = 0;
	if (tmp[0] == '>' || tmp[0] == '<')
	{
		while (tmp[i] == '>' || tmp[i] == '<')
			i++;
		if (i == ft_strlen(tmp))
			return(2);
		else
			return(1);
	}
	return (1);
}
