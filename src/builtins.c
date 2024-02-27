/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:17:24 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/27 12:53:18 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	env(char **envp)
{
	if (!envp)
		return ;
	while (*envp)
		printf("%s\n",*(envp)++);
}

void	cd(char **cmd, char **envp)
{
	int	tablen;

	tablen = tablength(cmd);
	if (tablen > 2)
		return ;//error
	else if (tablen == 1)
		chdir(pathenv(envp, "HOME"));
	else
		chdir(cmd[1]);
}
