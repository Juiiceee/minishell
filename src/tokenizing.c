/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:00:02 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/11 18:00:14 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*tokenizing_redirect(char **tmp, int *i)
{
	int		j;
	char	**buff;

	j = 0;
	while (tmp[*i][j] == '>' || tmp[*i][j] == '<')
		j++;
	if (j > 2)
		return (tok_lstnew(ft_subtab(tmp, *i, 1), DONT_EXIST));
	else if (j == (int)ft_strlen(tmp[*i]))
	{
		if (tmp[*i][0] == '<')
			return (tok_lstnew(ft_subtab(tmp, *i, 2), IN_REDIRECT));
		else
			return (tok_lstnew(ft_subtab(tmp, *i, 2), OU_REDIRECT));
	}
	else if (j != (int)ft_strlen(tmp[*i]))
	{
		buff = malloc((sizeof (char *)) * 3);
		buff[0] = ft_substr(tmp[*i], 0, j);
		buff[1] = ft_substr(tmp[*i], j, ft_strlen(tmp[*i]) - j);
		buff[2] = 0;
		if (tmp[*i][0] == '<')
			return (tok_lstnew(buff, IN_REDIRECT));
		else if (tmp[*i][0] == '>')
			return (tok_lstnew(buff, OU_REDIRECT));
	}
	return (NULL);
}

t_token	*tokenizing_pipe(char **tmp, int *i)
{
	t_token	*node;

	if (ft_strlen(tmp[*i]) == 1)
		node = tok_lstnew(ft_subtab(tmp, *i, 1), PIPE);
	else
		node = tok_lstnew(ft_subtab(tmp, *i, 1), DONT_EXIST);
	*i += 1;
	return (node);
}

t_token	*tokenizing_other(char **tmp, int *i)
{
	int		j;
	t_token	*node;

	j = *i;
	while (tmp[j] != 0)
	{
		if ((tmp[j][0] == '|' && ft_strlen(tmp[j]) == 1) ||
				(tmp[j][0] == '<' || tmp[j][0] == '>'))
			break ;
		if (tmp[j][0] == '"' || tmp[j][0] == '\'')
		{
			tmp[j] = cut_first_char(tmp[j]);
			if (tmp[j] == NULL)
			{
				node = tok_lstnew(ft_subtab(tmp, *i, j + 1 - *i), DONT_EXIST);
				return (node);
			}
		}
		j++;
	}
	node = tok_lstnew(ft_subtab(tmp, *i, j - *i), CMD);
	*i = j;
	return (node);
}
