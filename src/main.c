/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 17:49:02 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini mini;
	char	*tmp;
	char	*tmp2;
	int	running;
	(void)argv;

	if (argc != 1)
		return (1);
	init(&mini, env);
	running = 1;
	while (running)
	{
		recocp(&mini);
		tmp = ft_strjoin(getenv("USER"), "@minishell:");
		tmp2 = ft_strjoin(tmp, mini.currentpath);
		free(tmp);
		mini.userstr = ft_strjoin(tmp2, "$ ");
		free(tmp2);
		mini.input = readline(mini.userstr);
		add_history(mini.input);
		free(mini.userstr);
		if (!ft_strncmp(mini.input, "cd", 2))
			chdir("../");
	}
	freetab(mini.env);
	free(mini.user);
	return (0);
}
