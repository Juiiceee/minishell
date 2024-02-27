/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 14:22:48 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*int	parsingcommand(t_pipex *pipex, char **argv, int nb)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strlen(argv[nb]) == 0)
		return (0);
	pipex->argcmd = ft_split(argv[nb], ' ');
	if (access(pipex->argcmd[0], X_OK))
	{ 
		if (!pipex->envpath)
			return (0);
		while (pipex->envpath[i])
		{
			tmp = ft_strjoin(pipex->envpath[i], "/");
			pipex->cmd = ft_strjoin(tmp, pipex->argcmd[0]);
			free(tmp);
			if (!access(pipex->cmd, X_OK))
				return (1);
			free(pipex->cmd);
			i++;
		}
		return (0);
	}
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	return (1);
}*/

void	ft_parse_exec(t_mini *mini)
{
	t_token *tmp;

	tmp = mini->lst;
	mini->exe = NULL;
	mini->pipe_nb = 0;
	while (tmp)
	{
		exe_lstadd_back(&mini->exe, exe_lstnew(tmp));
		while (tmp->data_type != PIPE && tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->data_type == PIPE && tmp->next)
		{
			tmp = tmp->next;
			mini->pipe_nb++;
		}
		else 
			break ;
	}
	mini->pipe = malloc(sizeof(int) * (mini->pipe_nb * 2));
}

void	ft_exec(t_mini *mini)
{
	while (mini->exe->next != NULL)
	{
		exec_node(mini->exe, mini->exe->next);
		mini->exe = mini->exe->next;
	}
}

void exec_node(t_exec *first, t_exec *second)
{
	
}