/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:30:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/09 13:17:59 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char **cmd, t_mini *mini)
{
	size_t	i;
	size_t  n;
	size_t	cmd_len;

	i = 1;
	n = 0;
	cmd_len = ft_tablen(cmd);
	if (cmd[1] && ft_strlen(cmd[1]))
		if (!ft_strncmp(cmd[1], "-n", ft_strlen(cmd[1])))
		{
			i++;
			n++;
		}
	while (i < cmd_len - 1)
		printf("%s ", cmd[i++]);
	if (cmd[i])
		printf("%s", cmd[i++]);
	if (!n)
		printf("\n");
	mini->exitstatus = 0;
	if (mini->pid == 0)
		exit(0);
}

void	ft_unset(char **cmd, t_mini *mini)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 1;
	while (cmd[j])
	{
		while (cmd[j][i] != '=' && cmd[j][i])
			i++;
		unset(mini, ft_substr(cmd[j], 0, i));
		i = 0;
		j++;
	}
	mini->exitstatus = 0;
	refreshtab(mini);
}
