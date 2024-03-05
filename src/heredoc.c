/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:19 by lbehr             #+#    #+#             */
/*   Updated: 2024/03/05 15:32:30 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *var_heredoc(char *tmp)
{
	int	i;
	int	j;
	char *newtmp;
	char *buff;

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
		return (free(newtmp),tmp);
	}
	newtmp = ft_strdup(getenv(newtmp));
	tmp = free_and_join(tmp, newtmp);
	tmp = free_and_join(tmp, buff);
	return (tmp);
}

int	heredoc(char *limiter)
{
	int		heredoc;
	char	*line;
	char	*tmp;

	unlink(".heredoc");
	heredoc = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!heredoc)
		return (perror("open heredoc"), 1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			break;
		if (ft_strchr(line, '$'))
			var_dquote(line);
		tmp = ft_strjoin(line, "\n");
		if (!tmp)
			return (perror("Malloc"), 1);
		write(heredoc, tmp, ft_strlen(tmp));
		free(tmp);
	}
	return (heredoc);
}
