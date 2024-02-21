/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 15:31:30 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init(t_mini *mini, char **env)
{
	if (recoenv(env, mini))
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_mini mini;
	int	running;
	(void)argv;

	if (argc != 1)
		return (1);
	if (init(&mini, env))
		return (1);
	freetab(mini.env);
	return (0);
}