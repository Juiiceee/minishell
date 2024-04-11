/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dquote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:07:22 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/11 14:24:58 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_code_dquote(t_mini *mini, char *tmp, int i, int j)
{
	char	*newtmp;
	char	*buff;
	buff = ft_substr(tmp, j + 1, ft_strlen(tmp) - (j + 1));
	tmp = sub_and_free(tmp, 0, i);
	newtmp = ft_itoa(mini->exitstatus);
	tmp = free_and_join(tmp, newtmp);
	tmp = free_and_join(tmp, buff);
	return (tmp);
}

char	*var_dquote(char *tmp, t_mini *mini, int *index)
{
	int		i;
	int		j;
	char	*newtmp;
	char	*buff;

	i = 0;
	(void)*index;
	while (tmp[i] != '$')
		i++;
	j = i + 1;
	if (tmp[j] == '?')
		return (exit_code_dquote(mini, tmp, i, j));
	while (ft_isalnum(tmp[j]) && tmp[j])
		j++;
	newtmp = ft_substr(tmp, i + 1, j - i - 1);
	buff = ft_substr(tmp, j, ft_strlen(tmp) - j);
	tmp = sub_and_free(tmp, 0, i);
	if (!pathenv(mini, newtmp))
	{
		tmp = free_and_join(tmp, buff);
		return (free(newtmp), tmp);
	}
	tmp = free_and_join(tmp, ft_strdup(pathenv(mini, newtmp)));
	tmp = free_and_join(tmp, buff);
	return (free(newtmp), tmp);
}
