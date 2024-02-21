/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 16:39:04 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini mini;
	int	running;
	(void)argv;

	if (argc != 1)
		return (1);
	if (init(&mini, env))
		return (1);
		running = 1;
	while (running)
	{
		mini.userstr = ft_strjoin(mini.user, "@minishell$ ");
		mini.input = readline(mini.userstr);
		free(mini.userstr);
		add_history(mini.input);
	}
	freetab(mini.env);
	free(mini.user);
	return (0);
}