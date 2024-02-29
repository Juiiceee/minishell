/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:17:24 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/29 13:28:07 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	ft_env(t_mini *mini)
{
	if (!mini->env)
		return ;
	// while (t_mini *mini)
	// 	printf("%s\n",*(envp)++);
}

void	ft_cd(char **cmd, t_mini *mini)
{
	int	tablen;

	tablen = tablength(cmd);
	if (tablen > 2)
		return ;//error
	else if (tablen == 1)
		chdir(pathenv(mini, "HOME"));
	else
		chdir(cmd[1]);
}
void	ft_exit(void)
{
	printf("exit\n");
	exit(0);//error
}

void	ft_export(t_mini *mini, char *variable, char *value)
{
	export(mini, variable, value);
}
