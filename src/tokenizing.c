/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:00:02 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/24 11:59:25 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*tokenizing_redirect(char **tmp, int *i, t_token *lst)
{
	int j;
	char **buff;

	j = 0;
	while (tmp[*i][j] == '>' || tmp[*i][j] == '<')
		j++;
	if (j > 2)
		return(ms_lstnew(ft_subtab(tmp, *i, 1), DONT_EXIST));	
	else if (j == ft_strlen(tmp[*i]))
	{
		if (tmp[*i][0] == '<')
			return (ms_lstnew(ft_subtab(tmp, *i, 2), IN_REDIRECT));
		else if (tmp[*i][0] == '>')
			return (ms_lstnew(ft_subtab(tmp, *i, 2), OU_REDIRECT));
	}
	else if (j != ft_strlen(tmp[*i]))
	{
		buff = malloc((sizeof (char)) * 3);
		buff[0] = ft_substr(tmp[*i], 0, j);
		buff[1] = ft_substr(tmp[*i], j, ft_strlen(tmp[*i]) - j);
		buff[2] = 0;
		if (tmp[*i][0] == '<')
			return (ms_lstnew(buff, IN_REDIRECT));
		else if (tmp[*i][0] == '>')
			return (ms_lstnew(buff, OU_REDIRECT));
	}
	return(NULL);
}
