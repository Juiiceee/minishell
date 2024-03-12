/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:19 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/13 00:15:21 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_heredoc(char *tmp)
{
	int		i;
	int		j;
	char	*newtmp;
	char	*buff;

	i = 0;
	while (tmp[i] != '$')
		i++;
	j = i + 1;
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

int	heredoc(char *limiter)
{
	int		heredoc[2];
	char	*line;
	char	*tmp;

	if (pipe(heredoc) == -1)
		return(-1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		if (ft_strchr(line, '$'))
			var_heredoc(line);
		tmp = ft_strjoin(line, "\n");
		if (!tmp)
			return (perror("Malloc"), 1);
		write(heredoc[1], tmp, ft_strlen(tmp));
		free(tmp);
		free(line);
	}
	free(line);
	close(heredoc[1]);
	return (heredoc[0]);
}
