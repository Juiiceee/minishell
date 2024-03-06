/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:30:52 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/06 12:57:32 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_builtins(t_exec *exec, t_mini *mini)
{
	if (!ft_strncmp(exec->cmd[0], "echo", 4))
		ft_echo(exec->cmd, mini);
	else if (!ft_strncmp(exec->cmd[0], "cd", 2))
		ft_cd(exec->cmd, mini);
	else if (!ft_strncmp(exec->cmd[0], "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(exec->cmd[0], "export", 6))
		ft_export(exec->cmd, mini);
	else if (!ft_strncmp(exec->cmd[0], "unset", 5))
		ft_unset(exec->cmd, mini);
	else if (!ft_strncmp(exec->cmd[0], "env", 3))
		ft_env(mini);
	else if (!ft_strncmp(exec->cmd[0], "exit", 4))
		ft_exit(mini, exec->cmd);
}
