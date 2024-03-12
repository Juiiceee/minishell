/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:47:47 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/12 10:51:33 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_old_and_join(char *old, char *new)
{
	char	*tmp;

	tmp = ft_strjoin(old, new);
	free(old);
	return (tmp);
}

char	*free_new_and_join(char *old, char *new)
{
	char	*tmp;

	tmp = ft_strjoin(old, new);
	free(new);
	return (tmp);
}

char	*cut_first_char(char *old)
{
	char	*tmp;

	tmp = ft_substr(old, 1, ft_strlen(old) - 1);
	free(old);
	return (tmp);
}

char	**ft_tabjoin(char **s1, char **s2)
{
	char	**join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = ft_calloc((sizeof (char *)), (ft_tablen(s1) + ft_tablen(s2)) + 1);
	if (!join)
		return (NULL);
	while (i < ft_tablen(s1))
	{
		join[i] = s1[i];
		i++;
	}
	while (j < ft_tablen(s2))
	{
		join[i + j] = s2[j];
		j++;
	}
	return (join);
}
