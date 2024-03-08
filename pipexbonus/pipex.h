/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:58:14 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 16:25:53 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_pipex
{
	int		outfile;
	int		infile;
	int		*pipe;
	char	**envpath;
	char	*cmd;
	char	**argcmd;
	pid_t	pid;
	int		here_doc;
	int		nbcmd;
	int		nbpipe;
	int		indexpro;
}	t_pipex;

//ft_split.c
char	**ft_split(char const *s, char c);

//process.c
char	*pathenv(char **env);

//error.c

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif
