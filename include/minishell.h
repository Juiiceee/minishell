/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:45 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/22 19:26:50 by mda-cunh         ###   ########.fr       */
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
#include <signal.h>
#include "../libft/libft.h"

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
int		tablength(char **tab);
void	freetab(char **tab);

//env.c
int		recoenv(t_mini *mini, char **argv);
int		recocp(t_mini *mini);

//init.c
int		init(t_mini *mini, char **env);

//prompt.c
char	*pathenv(char **env, char *find);
int		recouser(t_mini *mini);
void	createprename(t_mini *mini);
void	prompt();
//running.c
void	running(t_mini *mini);
int		insiderunning(t_mini *mini);

//signal.c
void	recosignal();
void	recoSigint(int sig);

//parse_line.c
char	*squote_parse(char *input, int *index);
char	*dquote_parse(char *input, int *index);
char	*var_dquote(char *tmp);
char	*str_parse(char *input, int *index);
char	*punct_parse(char *input,int *i);

//utils.c
char	*free_and_join(char *old, char *new);

//token.c
void 	ft_tokenizer(char *input, t_mini *mini);
char	*ft_select_token(char *input, int *i);

#endif