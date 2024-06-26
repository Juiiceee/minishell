/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/29 14:46:12 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_and_join(char *old, char *new)
{
	char	*tmp;

	tmp = ft_strjoin(old, new);
	free(old);
	if (new)
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

char	**ft_subtab(char **tab, int start, int len)
{
	int		i;
	char	**sub;

	i = 0;
	if (!tab)
		return (NULL);
	if (start >= ft_tablen(tab))
		return (ft_calloc(1, 1));
	if (len > ft_tablen(tab))
		len = ft_tablen(tab);
	sub = malloc((sizeof (char *)) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && tab[start])
	{
		sub[i] = tab[start++];
		i++;
	}
	sub[i] = 0;
	return (sub);
}

int	isvar(char **env, char *var)
{
	int	check;
	int	lenght;
	int	i;

	i = 0;
	check = 1;
	if (!env || !env[0])
		return (-1);
	lenght = ft_strlen(var);
	while (check && env[i])
		check = ft_strncmp(var, env[i++], lenght);
	if (check == 0 && env[i])
		return (i);
	return (-1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s2[i] == '=' && s1[i])
			return (1);
		if (s2[i] == '=' && !s1[i])
			return (0);
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
