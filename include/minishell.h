#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct s_mini
{
	char **env;
}	t_mini;

//utilstab.c
int		tablength(char **tab);
void	freetab(char **tab);

#endif