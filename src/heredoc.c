/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:20:19 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/08 12:30:07 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signalexit;

char	*varparse(char *tmp, int j, int i, t_mini *mini)
{
	char	*newtmp;
	char	*buff;
	char	*swap;

	while (ft_isalnum(tmp[j]) && tmp[j])
		j++;
	newtmp = ft_substr(tmp, i + 1, j - i - 1);
	buff = ft_substr(tmp, j, ft_strlen(tmp) - j);
	tmp = sub_and_free(tmp, 0, i);
	if (!pathenv(mini, newtmp))
	{
		tmp = free_and_join(tmp, buff);
		return (free(newtmp), tmp);
	}
	swap = newtmp;
	newtmp = ft_strdup(pathenv(mini, newtmp));
	free(swap);
	tmp = free_and_join(tmp, newtmp);
	tmp = free_and_join(tmp, buff);
	return (tmp);
}

char	*var_heredoc(char *tmp, t_mini *mini)
{
	int		i;
	int		j;
	char	*newtmp;
	char	*buff;

	i = 0;
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
	return (varparse(tmp, j, i, mini));
}

char	*wait_line(char *line, t_mini *mini)
{
	int i;

	i = -1;
	while (line[++i] != 0)
		if (line[i] == '$' && (ft_isalnum(line[i + 1]) || line[i + 1] == '?'))
			line = var_heredoc(line, mini);
	return(line);
}

int	heredoc(char *limiter, t_mini *mini)
{
	int		heredoc[2];
	char	*line;
	char	*tmp;

	if (pipe(heredoc) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)) || g_signalexit == 130)
			break ;
		if (ft_strchr(line, '$'))
			line = wait_line(line, mini);
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

