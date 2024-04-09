/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   punct_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:50:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/09 14:51:06 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pipe_sign(char *input, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (input[j] == '|')
		j++;
	*i += j;
	tmp = ft_substr(input, 0, j);
	return (tmp);
}

char	*redirect_sign(char *input, int *i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (input[j] == '<' || input[j] == '>')
		j++;
	tmp = ft_substr(input, 0, j);
	*i = *i + j;
	return (tmp);
}

char *special_dolar_sign(char *input, t_mini *mini, int *i)
{
	if (!ft_isalnum(input[1]) || !input[1])
		return (*i = *i + 1, ft_strdup("$"));
	if (input[1] == '?')
		return (*i = *i + 2, free_and_join(ft_strdup("$"),
		ft_itoa(mini->exitstatus)));
	return (NULL);
}

char	*dollar_sign(char *input, int *i, t_mini *mini)
{
	int		j;
	char	*tmp;
	char 	*swap;

	j = 1;
	if (!ft_isalnum(input[1]) || !input[1])
		return(special_dolar_sign(input, mini, i));
	while ((ft_isalnum(input[j]) || input[j] == '_') && input[j])
		j++;
	tmp = ft_substr(input, 1, j - 1);
	*i += j;
	if (!tmp[0] || !pathenv(mini, tmp))
		return (free(tmp), NULL);
	else
	{
		swap = tmp;
		tmp = free_and_join(ft_strdup("$"), ft_strdup(pathenv(mini, tmp)));
		free(swap);
	}
	return (tmp);
}
