/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:23 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/11 13:08:49 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	escape_redirect(char *input, int *i)
{
	while (input[*i] == '<' || input[*i] == '>')
		*i = *i + 1;
	return (1);
}

int	escape_dolar(char *input, int *i, t_mini *mini)
{
	int		j;
	char	*tmp;
	char	*var;
	char	**tab;

	j = *i;
	j += 1;
	while (ft_isalnum(input[j]) && input[j])
		j++;
	tmp = ft_substr(input, *i + 1, j - *i - 1);
	*i = j;
	var = pathenv(mini, tmp);
	if (!var)
		return (free(tmp), 1);
	free (tmp);
	tab = ft_split(var, ' ');
	if (!tab)
		return (free(var), 0);
	j = ft_tablen(tab);
	ft_free(tab);
	return (j);
}

int	escape_quote(char *input, int *i)
{
	int	j;

	j = *i;
	while (input[++j])
	{
		if (input[j] == input[*i])
		{
			j++;
			break ;
		}
	}
	*i = j;
	return (1);
}

int	escape_word(char *input, int *i, t_mini *mini)
{
	int	j;

	j = *i;
	if (input[j] == '$')
		return (escape_dolar(input, i, mini));
	while (input[j])
	{
		if (input[j] == '|' || input[j] == '<'
			|| input[j] == '>'
			|| (ft_isspace(input[j])))
			break ;
		if (input[j] == '\'' || input[j] == '\"')
			escape_quote(input, &j);
		else
			j++;
	}
	*i = j;
	return (1);
}
