/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:35:23 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/28 16:04:01 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	escape_redirect(char *input, int *i)
{
	while (!ft_isalpha(input[*i]) && input[*i])
		*i = *i + 1;
	while (ft_isalpha(input[*i]) && input[*i])
		*i = *i + 1;
	return (1);
}

int	escape_quote(char *input, int *i)
{
	int j;

	j = *i + 1;
	while (input[j])
	{
		if (input[j] == input[*i])
		{
			j++;
			break ;
		}
		j++;
	}
	while (!isspace(input[j]))
	{
		if (input[j] == '\'' || input[j] == '\"')
		{
			*i = j;
			escape_quote(input, i);
			break ;
		}
		j++;
	}
	*i = j;
	return (1);
}

int	escape_word(char *input, int *i)
{
	int j;

	j = *i;
	while (input[j])
	{
		if ((input[j] == '|' && ft_strlen(input) == 1) || 
				(input[j] == '<' || input[j] == '>') || isspace(input[j]))
			break;
		j++;
	}
	*i = j;
	return (1);
}
