/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:36:30 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/09 15:26:51 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	modifievaluelst(t_list **st, char *find, char *new)
{
	char	*tmp;
	t_list	*lst;

	lst = *st;
	if (ft_strlen(new) == 0)
		lst->content = ft_strjoin(find, "=");
	else
	{
		free(lst->content);
		tmp = ft_strjoin(find, "=");
		lst->content = ft_strjoin(tmp, new);
		free(tmp);
	}
	return ;
}

void	addvaluelst(t_mini *mini, char *find, char *new)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(find, "=");
	if (ft_strlen(new) == 0)
		ft_lstadd_back(&mini->env, ft_lstnew(tmp));
	else
	{
		tmp1 = ft_strjoin(tmp, new);
		ft_lstadd_back(&mini->env, ft_lstnew(tmp1));
	}
	free(tmp);
}

void	export(t_mini *mini, char *find, char *new)
{
	int		check;
	char	*tmp;
	t_list	*st;

	st = mini->env;
	check = 1;
	if (!st)
	{
		addvaluelst(mini, find, new);
		return ;
	}
	tmp = ft_strjoin(find, "=");
	while (check && st->next != NULL)
	{
		check = ft_strncmp(tmp, (char *)st->content, ft_strlen(tmp));
		if (check == 0)
			break ;
		st = st->next;
	}
	check = ft_strncmp(tmp, (char *)st->content, ft_strlen(tmp));
	if (check == 0)
		modifievaluelst(&st, find, new);
	else
		addvaluelst(mini, find, new);
	return (free(tmp));
}

int	ft_checkexport(char **cmd, t_mini *mini, size_t j)
{
	size_t	i;

	i = 0;
	if (cmd[j][0] == '=')
	{
		while (cmd[j][i])
			i++;
		return (mini->exitstatus = 1,
			(void)ft_printerr("`%s': not a valid identifier",
				ft_substr(cmd[j], 0, i)), 1);
	}
	while (cmd[j][i] != '=' && cmd[j][i])
	{
		if (!ft_isalpha(cmd[j][i]))
			return (mini->exitstatus = 1,
				(void)ft_printerr("`%s': not a valid identifier",
					ft_substr(cmd[j], 0, ++i)), 1);
		i++;
	}
	if (isdigit(cmd[j][0]))
		return (mini->exitstatus = 1,
			(void)ft_printerr("`%s': not a valid identifier",
				ft_substr(cmd[j], 0, i)), 1);
	return (0);
}

void	exportsolo(t_mini *mini)
{
	t_list	*st;

	st = mini->env;
	while (st)
	{
		printf("declare -x %s\n", (char *)st->content);
		st = st->next;
	}
}
