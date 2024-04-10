/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:30:52 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/11 00:08:47 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_exec *exec, t_mini *mini)
{
	if (!ft_strcmp(exec->cmd[0], "echo"))
		ft_echo(exec->cmd, mini);
	else if (!ft_strcmp(exec->cmd[0], "cd"))
		ft_cd(exec->cmd, mini);
	else if (!ft_strcmp(exec->cmd[0], "pwd"))
		ft_pwd(mini);
	else if (!ft_strcmp(exec->cmd[0], "export"))
		ft_export(exec->cmd, mini);
	else if (!ft_strcmp(exec->cmd[0], "unset"))
		ft_unset(exec->cmd, mini);
	else if (!ft_strcmp(exec->cmd[0], "env"))
		ft_env(mini);
	else if (!ft_strcmp(exec->cmd[0], "exit"))
		ft_exit(mini, exec->cmd);
}
