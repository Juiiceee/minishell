/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/29 15:19:31 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	is_splitted(char **tmp, int *i)
{
	int	j;

	j = 0;
	if (tmp[*i][0] == '>' || tmp[*i][0] == '<')
	{
		while (tmp[*i][j] == '>' || tmp[*i][j] == '<')
			j++;
		if (j == (int)ft_strlen(tmp[*i]) && j <= 2 && !tmp[*i][j] && tmp[*i + 1])
			return (2);
		else if (tmp[*i][j] && j <= 2)
			return (free(tmp[*i]), 1);
	}
	return (1);
}
