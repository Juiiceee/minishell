/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:32:26 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/09 17:20:03 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			|| input[i] == '$')
			break ;
	tmp = malloc((sizeof (char)) * i + 1);
	while (++j <= i)
		tmp[j] = input[j];
	tmp[j - 1] = '\0';
	*index = *index + i;
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
	{
		buff = ft_substr(tmp, j + 1, ft_strlen(tmp) - (j + 1));
		tmp = ft_substr(tmp, 0, i);
		newtmp = ft_itoa(mini->exitstatus);
		tmp = free_and_join(tmp, newtmp);
		tmp = free_and_join(tmp, buff);
		return (tmp);
	}
	while (ft_isalnum(tmp[j]) && tmp[j])
		j++;
	newtmp = ft_substr(tmp, i + 1, j - i - 1);
	buff = ft_substr(tmp, j, ft_strlen(tmp) - j);
	tmp = ft_substr(tmp, 0, i);
	if (!getenv(newtmp))
	{
		tmp = free_and_join(tmp, buff);
		return (free(newtmp), tmp);
	}
	newtmp = ft_strdup(getenv(newtmp));
	tmp = free_and_join(tmp, newtmp);
	tmp = free_and_join(tmp, buff);
	return (tmp);
}

char	*dquote_parse(char *input, int *index, t_mini *mini)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = -1;
	while (input[++i])
		if (input[i] == '"')
			break ;
	if (isspace(input[-1]))
		tmp = ft_substr(input, 0, i);
	else
		tmp = ft_substr(input, 1, i - 1);
	while (input[++j] != 0)
		if (input[j] == '$' && (ft_isalnum(input[j + 1]) || input[j + 1] == '?'))
			tmp = var_dquote(tmp, mini, index);
	*index = *index + i + 1;
	return (tmp);
}

char	*squote_parse(char *input, int *index)
{
	int		i;
	char	*tmp;

	i = 0;
	while (input[++i])
		if (input[i] == '\'')
			break ;
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
