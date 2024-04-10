/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:19:46 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/10 16:34:27 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exportvalueseul(t_mini *mini, char *find)
{
	t_list	*st;

	st = mini->env;
	if (!st || !st->content)
		return ;
	if (!pathenv(mini, find))
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(find)));
	return ;
}

void	freesub(t_mini *mini, char **cmd, size_t j, size_t	i)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_substr(cmd[j], 0, i);
	tmp1 = ft_substr(cmd[j], i + 1, ft_strlen(cmd[j]) - i - 1);
	export(mini, tmp, tmp1);
	return (free(tmp), free(tmp1));
}

int	ft_alphaunderscore(char c)
{
	if (ft_isalpha(c) || c == '_' || ft_isdigit(c))
		return (0);
	return (1);
}

void	printexe(int i, char *str)
{
	if (i == 1)
		return (ft_putstr_fd("'", 2), ft_putstr_fd(str, 2),
			ft_putstr_fd("': not a valid identifier", 2), free(str));
	else if (i == 2)
		return (ft_putstr_fd("exit: ", 2), ft_putstr_fd(str, 2),
			ft_putstr_fd(": numeric argument required\n", 2));
	else if (i == 3)
		return (ft_putstr_fd("cd: ", 2), ft_putstr_fd(str, 2),
			ft_putstr_fd(": No such file or directory\n", 2));
	else if (i == 4)
		return (ft_putstr_fd("Dquote is badly closed: ", 2),
			ft_putstr_fd(str, 2), ft_putstr_fd("\n", 2));
	else if (i == 5)
		return (ft_putstr_fd("Squote is badly closed: ", 2),
			ft_putstr_fd(str, 2), ft_putstr_fd("\n", 2));
	else if (i == 6)
		return (ft_putstr_fd("infile error :", 2),
			ft_putstr_fd(str, 2), ft_putstr_fd("\n", 2));
	else if (i == 7)
		return (ft_putstr_fd("outfile error :", 2),
			ft_putstr_fd(str, 2), ft_putstr_fd("\n", 2));
	else if (i == 8)
		return (ft_putstr_fd(str, 2), ft_putstr_fd(": Is a directory\n", 2));
}

void	printflu(int i, char *str)
{
	if (i == 9)
		return (ft_putstr_fd(str, 2),
			ft_putstr_fd(": No such file or directory\n", 2));
	else if (i == 10)
		return (ft_putstr_fd(str, 2),
			ft_putstr_fd(": Permission denied\n", 2));
	else if (i == 11)
		return (ft_putstr_fd(str, 2),
			ft_putstr_fd(": command not found\n", 2));
}
