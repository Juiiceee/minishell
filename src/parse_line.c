/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:32:26 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 17:31:59 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*punct_parse(char *input,int *i)
{
	char *tmp;
	
	if (input[0] == '$')
		tmp = dollar_sign(input, i);
	if (input[0] == '>' || input[0] == '<')
		tmp = redirect_sign(input,  i);
	if  (input[0] == '|')
		tmp = pipe_sign(input,  i);
	return (tmp);
}

char	*str_parse(char *input, int *index)
{
	int i = -1;
	int j = -1;
	char *tmp;

	while (input[++i])
		if (!ft_isprint(input[i]))
			break ;
	tmp = malloc((sizeof (char)) * i + 1);
	while (++j <= i)
		tmp[j] = input[j];
	tmp[j - 1] = '\0';
	*index = *index + i;
	return (tmp);
}

char *var_dquote(char *tmp)
{
	int	i;
	int	j;
	char *newtmp;
	char *buff;

	i = 0;
	while (tmp[i] != '$')
		i++;
	j = i + 1;
	while (isalpha(tmp[j]) && tmp[j])
		j++;
	newtmp = ft_substr(tmp, i + 1, j - i - 1);
	buff = ft_substr(tmp, j, ft_strlen(tmp) - j);
	tmp = ft_substr(tmp, 0, i);
	if (!getenv(newtmp))
	{
		tmp = free_and_join(tmp, buff);
		return (free(newtmp),tmp);
	}
	newtmp = ft_strdup(getenv(newtmp));
	tmp = free_and_join(tmp, newtmp);
	tmp = free_and_join(tmp, buff);
	return (tmp);
}

char	*dquote_parse(char *input, int *index)
{
	int i = -1;
	int j = -1;
	char *tmp;

	while (input[++i])
		if (input[i] == '"')
			break ;
	tmp = malloc((sizeof (char)) * i + 1);
	while (++j <= i)
		tmp[j] = input[j];
	tmp[j - 1] = '\0';
	j = 0;
	while (tmp[j])
		if (tmp[j++] == '$')
			tmp = var_dquote(tmp);
	*index = *index + i + 2;
	return (tmp);
}

char	*squote_parse(char *input, int *index)
{
	int i = -1;
	int j = -1;
	char *tmp;

	while (input[++i])
		if (input[i] == '\'')
			break ;
	tmp = malloc((sizeof (char)) * i + 1);
	while (++j <= i)
		tmp[j] = input[j];
	tmp[j - 1] = '\0';
	*index = *index + i + 2;
	return (tmp);
}