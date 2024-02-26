/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:55:42 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/26 15:25:24 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	isheredoc(t_pipex *pipex, char *str)
{
	if (ft_strncmp(str, "<<", 2))
		pipex->here_doc = 0;
	else
		pipex->here_doc = 1;
	return ;
}

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	setif(t_pipex *pipex, char *str)
{
	isheredoc(pipex, str);
	if (pipex->here_doc)
		;
}

void	pexrror(char *str, t_pipex *pipex)
{
	if (pipex->infile < 0)
		pipex->infile = open("/dev/null", O_RDONLY);
	else if (pipex->pipe < 0)
	{
		/*perror(str);
		closefile(pipex);
		exit(1);*/
	}
	perror(str);
}

void	closepipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbpipe)
		close(pipex->pipe[i++]);
}

void	closefilepipe(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
	free(pipex->pipe);
	return ;
}

void	createpipe(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->nbcmd - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			closefilepipe(pipex);
		i++;
	}
}

int	initnb(t_pipex *pipex, int argc)
{
	pipex->nbcmd = argc - 3 - pipex->here_doc;
	pipex->nbpipe = 2 * (pipex->nbcmd - 1);
	pipex->pipe = malloc(sizeof(int) * pipex->nbpipe);
	pipex->indexpro = 0;
	if (!pipex->pipe)
		return (1);
	return (0);
}

int	parsingcommand(t_pipex *pipex, char **argv, int nb)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strlen(argv[nb]) == 0)
		return (1);
	pipex->argcmd = ft_split(argv[nb], ' ');
	if (access(pipex->argcmd[0], X_OK))
	{ 
		if (!pipex->envpath)
			return (1);
		while (pipex->envpath[i])
		{
			tmp = ft_strjoin(pipex->envpath[i], "/");
			pipex->cmd = ft_strjoin(tmp, pipex->argcmd[0]);
			free(tmp);
			if (!access(pipex->cmd, X_OK))
				return (0);
			free(pipex->cmd);
			i++;
		}
		return (1);
	}
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	return (0);
}

void	process(t_pipex pipex, char **argv, char **env)
{
	pipex.pid = fork();
	if (pipex.pid == 0)
	{
		if (pipex.indexpro == 0)
		{
			dup2(pipex.infile,0);
			dup2(pipex.pipe[1], 1);
		}
		else if (pipex.indexpro == pipex.nbcmd - 1)
		{
			dup2(pipex.pipe[2 * pipex.indexpro - 2],0);
			dup2(pipex.outfile, 1);
		}
		else
		{
			dup2(pipex.pipe[2 * pipex.indexpro - 2],0);
			dup2(pipex.pipe[2 * pipex.indexpro + 1],1);
		}
		closepipe(&pipex);
		if (parsingcommand(&pipex, argv, 2 + pipex.indexpro)){}
			//erreur command not found
		if (execve(pipex.cmd, pipex.argcmd, env) == -1){}
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;
	//int		status;

	if (argc < 5)
		return (write(2, "Ambiguous Arguments\n", 21), 1);
	isheredoc(&pipex, argv[1]);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		pexrror("open infile", &pipex);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		;
	if (initnb(&pipex, argc))
		return (1);
	pipex.envpath = ft_split(pathenv(env), ':');
	if (!pipex.envpath)
		closefilepipe(&pipex);
	createpipe(&pipex);
	while (pipex.indexpro < pipex.nbcmd)
	{
		process(pipex, argv, env);
		pipex.indexpro++;
	}
	closepipe(&pipex);
	free(pipex.pipe);
	freetab(pipex.envpath);
	close(pipex.infile);
	close(pipex.outfile);
	waitpid(-1, NULL, 0);
	return (/*WEXITSTATUS(status)*/0);
}
