/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:17:24 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/03 16:15:51 by lbehr            ###   ########.fr       */
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
	t_list *str;

	str = mini->env;
	if (!mini->env)
		return ;
	while (str->next != NULL)
	{
	 	printf("%s\n", (char *)str->content);
		str = str->next;
	}
	printf("%s\n", (char *)str->content);
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

void ft_export(char **cmd, t_mini *mini)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 1;
	/*if (ft_strnb(cmd[j],'=') > 1)
	{
		printf()
	}*/
	if (!cmd[1])
		return (exportsolo(mini));
	while (cmd[j])
	{
		while (cmd[j][i] != '=' && cmd[j][i])
			i++;
		if (cmd[j][0] != '=' && ft_strchr(cmd[j], '=') && ft_strlen(cmd[j]) != i)
			export(mini, ft_substr(cmd[j], 0, i), ft_substr(cmd[j], i + 1, ft_strlen(cmd[j]) - i - 1));
		i = 0;
		j++;
	}
	refreshtab(mini);
}