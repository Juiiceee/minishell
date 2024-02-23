/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/23 15:38:10 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*free_and_join(char *old, char *new)
{
	char	*tmp;

	tmp = ft_strjoin (old, new);
	free(old);
	free(new);
	return (tmp);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char **ft_subtab(char **tab, int start, int len)
{
	unsigned int	i;
	char			**sub;

	i = 0;
	if (!tab)
		return (NULL);
	if (start >= (unsigned int)ft_tablen(tab))
		return (ft_calloc(1, 1));
	if (len > ft_tablen(tab))
		len = ft_tablen(tab);
	sub = malloc((sizeof (char *)) * (len + 1));
	if (!sub)
		return (NULL);
	while (start < len && tab[start])
	{
		sub[i] = tab[start++];
		i++;
	}
	sub[start] = '\0';
	return (sub);
}