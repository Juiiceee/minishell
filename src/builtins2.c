/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:30:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/01 14:02:40 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char **cmd)
{
	size_t	i;
	size_t  n;
	size_t	cmd_len;

	i = 1;
	n = 0;
	cmd_len = ft_tablen(cmd);
	if (cmd[1])
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
}
