/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:06:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/29 14:12:43 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execlear(t_exec **lst, void (*del)(char **))
{
	t_exec	*actual;
	t_exec	*sav;

	if (!del || !lst)
		return ;
	actual = *lst;
	while (actual)
	{
		sav = actual->next;
		if (actual->cmd)
			(*del)(actual->cmd);
		if (actual->is_fdin == 1)
			close(actual->fdin);
		if (actual->in)
			(*del)(actual->in);
		if (actual->is_fdout == 1)
			close(actual->fdout);
		if (actual->out)
			(*del)(actual->out);
		free(actual);
		actual = sav;
	}
	*lst = NULL;
}

void	ft_tokclear_str(t_token **lst)
{
	t_token	*actual;
	t_token	*sav;

	if (!lst)
		return ;
	actual = *lst;
	while (actual)
	{
		sav = actual->next;
		ft_free(actual->global);
		free(actual);
		actual = sav;
	}
	*lst = NULL;
}

void	ft_tokclean(t_token **lst)
{
	t_token	*actual;
	t_token	*sav;

	if (!lst)
		return ;
	actual = *lst;
	while (actual)
	{
		sav = actual->next;
		free(actual);
		actual = sav;
	}
	*lst = NULL;
}

void	ft_envclean(t_list **lst)
{
	t_list	*actual;
	t_list	*sav;

	if (!lst)
		return ;
	actual = *lst;
	while (actual->next != NULL)
	{
		sav = actual->next;
		free(actual->content);
		free(actual);
		actual = sav;
	}
	if (actual->content)
		free(actual->content);
	free(actual);
	*lst = NULL;
}
