/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:30:52 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/01 12:35:52 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_builtins(char **cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd[0], "echo", 4))
		ft_echo(cmd);
	if (!ft_strncmp(cmd[0], "cd", 2))
		ft_cd(cmd, mini);
	if (!ft_strncmp(cmd[0], "pwd", 3))
		ft_pwd();
	if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd, mini);
	if (!ft_strncmp(cmd[0], "unset", 5))
		return ;
	if (!ft_strncmp(cmd[0], "env", 3))
		ft_env(mini);
	if (!ft_strncmp(cmd[0], "exit", 4))
		ft_exit();
	if (!ft_strncmp(cmd[0], "meow", 4))
		return ;
}
