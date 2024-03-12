/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:55 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 10:51:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;

	(void)argv;
	if (argc != 1)
		return (1);
	init(&mini, env);
	recosignal();
	running(&mini);
	freetab(mini.tabenv);
	free(mini.user);
	return (mini.exitstatus);
}
