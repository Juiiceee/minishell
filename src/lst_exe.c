/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:20:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/09 14:22:43 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_new_null(t_exec *new)
{
	new->builtin = 0;
	new->cmd = NULL;
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
}

int	is_a_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	if (!ft_strncmp(cmd, "export", 6))
		return (1);
	if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	if (!ft_strncmp(cmd, "env", 3))
		return (1);
	if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	if (!ft_strncmp(cmd, "meow", 4))
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
