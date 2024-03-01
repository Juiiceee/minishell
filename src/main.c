/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/29 12:39:11 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argv;
	if (argc != 1)
		return (1);
	init(&mini, env);
	recosignal();
	running(&mini);
	//freelst(mini.env);
	freetab(mini.tabenv);
	free(mini.user);
	return (0);
}
