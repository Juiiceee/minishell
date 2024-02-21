/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:45 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/21 16:17:26 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

typedef struct s_mini
{
	char	*user;
	char	*input;
	char	**env;
}	t_mini;

//utilstab.c
int		tablength(char **tab);
void	freetab(char **tab);

//env.c
int		recoenv(t_mini *mini, char **argv);

//init.c
int		init(t_mini *mini, char **env);

//prompt.c
char	*pathenv(char **env, char *find);
int		recouser(t_mini *mini);

#endif