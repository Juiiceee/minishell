/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/11 00:10:12 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_new_null(t_exec *new)
{
	new->builtin = 0;
	new->cmd = NULL;
	new->in = NULL;
	new->out = NULL;
	new->fdin = 0;
	new->fdout = 0;
	new->is_fdout = 0;
	new->is_fdin = 0;
	new->next = NULL;
}

int	is_a_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "meow"))
		return (1);
	return (0);
}

t_exec	*exe_lstnew(t_token *tmp)
{
	t_exec	*newlst;

	newlst = malloc(sizeof (*newlst));
	init_new_null(newlst);
	if (!newlst)
		return (NULL);
	while (tmp && tmp->data_type != PIPE)
	{
		if (tmp->data_type == CMD)
			if (is_a_builtin(tmp->global[0]))
				newlst->builtin = 1;
		if (tmp->data_type == CMD && newlst->cmd)
			newlst->cmd = ft_tabjoin(newlst->cmd, tmp->global);
		else if (tmp->data_type == CMD && !newlst->cmd)
			newlst->cmd = tmp->global;
		if (tmp->data_type == IN_REDIRECT)
			parse_redirect_in(tmp, newlst);
		if (tmp->data_type == OU_REDIRECT)
			parse_redirect_out(tmp, newlst);
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
