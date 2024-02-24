/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:45 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 16:33:25 by mda-cunh         ###   ########.fr       */
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

typedef enum e_type
{
	CMD,
	IN_REDIRECT,
	OU_REDIRECT,
	APPEND,
	HERE_DOC,
	PIPE,
	DONT_EXIST
}	t_type;

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

typedef struct s_token
{
	char	**global;
	t_type	data_type;
	struct s_token *next;
}	t_token;


typedef struct s_exec
{
	char	**cmd;
}	t_exec;

typedef struct s_mini
{
	char	*currentpath;
	char	*userstr;
	char	*user;
	char	*input;
	char	**env;
	t_token *lst;
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
char	**ft_subtab(char **tab, int start, int len);
int		ft_tablen(char **tab);

//tokenizer.c
t_token	*ft_tokenizer(char *input);
char	*ft_select_token(char *input, int *i);
t_token *listing_token(char **tmp);

//tokenizing.c
t_token	*tokenizing_redirect(char **tmp, int *i);
t_token *tokenizing_pipe(char **tmp, int *i);
t_token *tokenizing_other(char **tmp, int *i);

//punct_handle.c
char 	*dollar_sign(char *input, int *i);
char 	*redirect_sign(char *input, int *i);
char 	*pipe_sign(char *input, int *i);

//lst_utils.c
t_token	*ms_lstnew(char **content, t_type data);
void	ms_lstadd_back(t_token **lst, t_token *new);
t_token	*ms_lstlast(t_token *lst);
int		is_splitted(char *tmp);

//exec.c
void	ft_exec(t_token *lst)

#endif