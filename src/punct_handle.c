/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   punct_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:50:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/03 13:36:45 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern int	exitstatus;

char 	*pipe_sign(char *input, int *i)
{
	int j;
	char *tmp;

	j = 0;
	while (input[j] == '|')
		j++;
	*i += j;
	tmp = ft_substr(input, 0,  j);
	return (tmp);
}

char 	*redirect_sign(char *input, int *i)
{
	int j;
	char *tmp;


	j = 0;
	while (input[j] == '<' || input[j] == '>')
		j++;
	*i += j;
	tmp = ft_substr(input, 0,  j);
	return (tmp);
}

char 	*dollar_sign(char *input, int *i, t_mini *mini)
{
	int		j;
	char	*tmp;
	(void) mini;

	j = 1;
	*i += 1;
	if (isspace(input[1]))
		return (ft_strdup("$"));
	if (input[1] == '?')
		j++;
	while ((isalpha(input[j]) && input[j]))
		j++;
	tmp = ft_substr(input, 1, j - 1);
	*i += ft_strlen(tmp);
	if (input[1] == '?')
		return (free_and_join(ft_strdup("$"), ft_itoa(mini->exitstatus)));
	if (!getenv(tmp))
		return (free(tmp), ft_strdup(""));
	else
		tmp = free_and_join(ft_strdup("$"), ft_strdup(getenv(tmp)));
	return(tmp);
}
