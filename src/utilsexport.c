/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsexport.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:19:46 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/12 16:28:05 by lbehr            ###   ########.fr       */
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
	if (ft_isalpha(c) || c == '_')
		return (0);
	return (1);
}
