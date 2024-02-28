/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:32:33 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/28 14:18:51 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*pathenv(t_mini *mini, char *find)
{
	int	check;
	int	lenght;

	check = 1;
	if (!mini->env || !mini->env->content)
		return (NULL);
	lenght = ft_strlen(find);
	while (check && mini->env->next)
	{
		mini->env = mini->env->next;
		check = ft_strncmp(find, (char *)mini->env->content, lenght);
	}
	if (check == 0)
		return ((char *)mini->env->content + (lenght + 1));
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
