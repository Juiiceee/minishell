/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:45 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 09:58:36 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

typedef enum e_builtins
{
	CD,
	ECHO,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtins;

typedef struct s_mini
{
	char	*currentpath;
	char	*userstr;
	char	*user;
	char	*input;
	char	**env;
}	t_mini;

//utilstab.c
int				tablength(char **tab);
void			freetab(char **tab);

//env.c
int				recoenv(t_mini *mini, char **argv);
int				recocp(t_mini *mini);

//init.c
int				init(t_mini *mini, char **env);

//prompt.c
char			*pathenv(char **env, char *find);
int				recouser(t_mini *mini);
void			createprename(t_mini *mini);
void			prompt(void);
//running.c
void			running(t_mini *mini);
int				insiderunning(t_mini *mini);

//signal.c
void			recosignal(void);
static void		recoSigint(int sig);
static void		recoSigquit(int sig);

#endif