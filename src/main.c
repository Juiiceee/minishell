/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 17:10:56 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **env)
{
	t_mini mini;
	int	running;
	(void)argv;

	if (argc != 1)
		return (1);
	// if (init(&mini, env))
		// return (1);
	init(&mini, env);	
	running = 1;
	while (running)
	{
		mini.userstr = ft_strjoin(getenv("USER"), "@minishell$ ");
		mini.input = readline(mini.userstr);
		add_history(mini.input);
		free(mini.userstr);
	}
	freetab(mini.env);
	free(mini.user);
	return (0);
}