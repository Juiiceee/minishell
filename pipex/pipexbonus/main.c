/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:55:42 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 16:35:38 by lbehr            ###   ########.fr       */
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
	while (i < pipex->nbpipe -1)
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
		//erroroutfile(&pipex, argv);
	if (initnb(&pipex, argc))
		return (1);
	pipex.envpath = ft_split(pathenv(env), ':');
	if (!pipex.envpath)
		closefilepipe(&pipex);
	createpipe(&pipex);
	while (pipex.indexpro < pipex.nbcmd)
	{
		
		pipex.indexpro++;
	}
	return (/*WEXITSTATUS(status)*/0);
}
