/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:32:26 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/11 14:27:47 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*punct_parse(char *input, int *i, t_mini *mini, int *j)
{
	char	*tmp;

	if (input[0] == '$')
	{
		tmp = dollar_sign(input, i, mini);
		if (ft_strlen(tmp) > 1)
			tmp = split_env(tmp, mini->tabcmd, j);
	}
	if (input[0] == '>' || input[0] == '<')
		tmp = redirect_sign(input, i);
	if (input[0] == '|')
		tmp = pipe_sign(input, i);
	return (tmp);
}

char	*str_parse(char *input, int *index)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = -1;
	while (input[++i])
		if (!ft_isprint(input[i]) || input[i] == '\'' || input[i] == '"'
			|| input[i] == '$' || input[i] == '>' || input[i] == '<'
			|| input[i] == '|')
			break ;
	tmp = malloc((sizeof (char)) * i + 1);
	while (++j <= i)
		tmp[j] = input[j];
	tmp[j - 1] = '\0';
	*index = *index + i;
	return (tmp);
}

char	*dquote_parse(char *str, int *index, t_mini *mini)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = -1;
	while (str[++i])
		if (str[i] == '"')
			break ;
	if (str[i] == '\0')
		return (*index = *index + i, ft_printerr("Dquote is badly closed, followed string as been voided : %s\n", str), NULL);
	if (*index != 0)
	{
		if (isspace(str[-1]))
			tmp = ft_substr(str, 0, i);
		else
			tmp = ft_substr(str, 1, i - 1);
	}
	else
		tmp = ft_substr(str, 0, i);
	while (str[++j] != 0 && str[j + 1] != '"' && (tmp[0] != 0 || tmp[j] != 0))
		if (str[j] == '$'
			&& (ft_isalnum(str[j + 1]) || str[j + 1] == '?'))
			tmp = var_dquote(tmp, mini, index);
	return (*index = *index + i + 1, tmp);
}

char	*squote_parse(char *input, int *index)
{
	int		i;
	char	*tmp;

	i = 0;
	while (input[++i])
		if (input[i] == '\'')
			break ;
	if (input[i] == '\0')
	{
		*index = *index + i;
		ft_printerr("Squote is badly closed, followed string as been voided : %s\n", input);
		return (NULL);
	}
	if (*index != 0)
	{
		if (isspace(input[-1]))
			tmp = ft_substr(input, 0, i);
		else
			tmp = ft_substr(input, 1, i - 1);
	}
	else
		tmp = ft_substr(input, 0, i);
	*index = *index + i + 1;
	return (tmp);
}
