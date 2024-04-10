/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:29:47 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/10 15:50:46 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcd(t_mini *mini, char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		mini->exitstatus = 1;
		free(pwd);
		return (printexe(3, path), 1);
	}
	export(mini, "OLDPWD", pwd);
	free(pwd);
	pwd = getcwd(NULL, 0);
	export(mini, "PWD", pwd);
	free(pwd);
	mini->exitstatus = 0;
	return (0);
}
