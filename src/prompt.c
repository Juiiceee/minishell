/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:32:33 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 10:18:25 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pathenv(char **env, char *find)
{
	int	check;
	int	lenght;

	check = 1;
	if (!env || !env[0])
		return (NULL);
	lenght = ft_strlen(find);
	while (check && *env)
	{
		env++;
		check = ft_strncmp(find, *env, lenght);
	}
	if (check == 0 && *env != NULL)
		return (*env + (lenght + 1));
	return (NULL);
}

int	recouser(t_mini *mini)
{
	mini->user = ft_strdup(pathenv(mini->env, "USER"));
	if (!mini->user)
	{
		mini->user = ft_strdup(pathenv(mini->env, "LOGNAME"));
		if (!mini->user)
			return (1);
	}
	return (0);
}

void	prompt(void)
{
	t_mini	mini;

	write(1, "\n", 1);
	recocp(&mini);
	createprename(&mini);
	mini.input = readline(mini.userstr);
	if (ft_strlen(mini.input) != 0)
		add_history(mini.input);
	free(mini.userstr);
	free(mini.currentpath);
	if (!ft_strncmp(mini.input, "cd", 2))
		chdir("../");
	else if (!ft_strncmp(mini.input, "exit", 4))
		printf("exit\n");
}
