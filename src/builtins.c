/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:17:24 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 10:51:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_mini *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	mini->exitstatus = 0;
}

void	ft_env(t_mini *mini)
{
	t_list	*str;

	str = mini->env;
	if (!mini->env)
	{
		mini->exitstatus = 0;
		return ;
	}
	while (str->next != NULL)
	{
		if (ft_strchr((char *)str->content, '='))
		{
			write(1, (char *)str->content, ft_strlen((char *)str->content));
			write(1, "\n", 1);
		}
		str = str->next;
	}
	if (ft_strchr((char *)str->content, '='))
	{
		write(1, (char *)str->content, ft_strlen((char *)str->content));
		write(1, "\n", 1);
	}
	mini->exitstatus = 0;
	if (mini->exe_size != 1)
		exit(0);
}

void	ft_cd(char **cmd, t_mini *mini)
{
	char	*pwd;

	if (tablength(cmd) > 2)
	{
		mini->exitstatus = 1;
		return ((void)ft_printerr("cd: too many arguments\n"));
	}
	else if (tablength(cmd) == 1)
	{
		pwd = getcwd(NULL, 0);
		export(mini, "PWD", pwd);
		return ((void)(free(pwd), chdir(pathenv(mini, "HOME")),
			export(mini, "PWD", pathenv(mini, "HOME")), mini->exitstatus = 0));
	}
	else if (cmd[1][0] == '-' && ft_strlen(cmd[1]) == 1)
	{
		if (execcd(mini, pathenv(mini, "OLDPWD")))
			return ;
	}
	else
	{
		if (execcd(mini, cmd[1]))
			return ;
	}
}

void	ft_exit(t_mini *mini, char **cmd)
{
	int	i;

	i = 0;
	if (tablength(cmd) > 2)
	{
		mini->exitstatus = 1;
		return ((void)ft_printerr("cd: too many arguments\n"));
	}
	printf("exit\n");
	ft_envclean(&mini->env);
	if (!cmd[1])
		exit(mini->exitstatus);
	if (cmd[1][0] == '+' || cmd[1][0] == '-')
		i++;
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			ft_printerr("exit: %s: numeric argument required\n", cmd[1]);
			exit(2);
		}
		i++;
	}
	exit(ft_atoi(cmd[1]));
}

void	ft_export(char **cmd, t_mini *mini)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 1;
	if (!cmd[1])
		return (exportsolo(mini));
	while (cmd[j])
	{
		if (ft_checkexport(cmd, mini, j))
			return ;
		while (cmd[j][i] != '=' && cmd[j][i])
			i++;
		if (!ft_strchr(cmd[j], '=') || cmd[j][i + 1] == '\0')
			exportvalueseul(mini, cmd[j]);
		if (cmd[j][0] != '=' && ft_strchr(cmd[j], '=')
			&& ft_strlen(cmd[j]) != i)
			freesub(mini, cmd, j, i);
		i = 0;
		j++;
	}
	refreshtab(mini);
	if (mini->exe_size != 1)
		exit(0);
}
