/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:17:24 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/27 15:12:48 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	PWD(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	ENV(char **envp)
{
	if (!envp)
		return ;
	while (*envp)
		printf("%s\n",*(envp)++);
}

void	CD(char **cmd, char **envp)
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
void	EXIT()
{
	printf("exit\n");
	exit(0);//error
}

void	EXPORT(t_mini *mini)
{
	
}
