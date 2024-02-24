/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 13:29:42 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 16:19:26 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*pathenv(char **env)
{
	int	check;

	check = 1;
	if (!env)
		return (NULL);
	while (check && *env)
	{
		env++;
		check = ft_strncmp("PATH", *env, 4);
	}
	if (check == 0)
		return (*env + 5);
	return (NULL);
}
