/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:45 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/29 13:17:44 by lbehr            ###   ########.fr       */
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
#include <fcntl.h>
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
	char	**in;
	int		in_fd;
	char	**out;
	int		out_fd;
	int		builtin;
	struct	s_exec *next;
}	t_exec;

typedef struct s_mini
{
	char	*currentpath;
	char	*userstr;
	char	*user;
	char	*input;
	t_list	*env;
	char	**tabenv;
	int		pipe[2];
	int		clear_fd;
	pid_t	pid;
	t_token *lst;
	t_exec *exe;
}	t_mini;

// utilstab.c
int				tablength(char **tab);
void			lsttotab(t_mini *mini);
void			refreshtab(t_mini *mini);

//free.c
void			freetab(char **tab);
void			freelst(t_list *lst);

// env.c
int				recoenv(t_mini *mini, char **argv);
int				recocp(t_mini *mini);

// init.c
int				init(t_mini *mini, char **env);

//prompt.c
char			*pathenv(t_mini *mini, char *find);
int				recouser(t_mini *mini);
void			createprename(t_mini *mini);
void			prompt(void);
// running.c
void			running(t_mini *mini);
int				insiderunning(t_mini *mini);

// signal.c
void			recosignal(void);

//export.c
void	modifievaluelst(t_list **st, char *find, char *new);
void	addvaluelst(t_mini *mini, char *find, char *new);
void	export(t_mini *mini, char *find, char *new);

// parse_line.c
char	*squote_parse(char *input, int *index);
char	*dquote_parse(char *input, int *index);
char	*var_dquote(char *tmp);
char	*str_parse(char *input, int *index);
char	*punct_parse(char *input,int *i);

// utils.c
char	*free_and_join(char *old, char *new);
char	**ft_subtab(char **tab, int start, int len);
int		ft_tablen(char **tab);
void	closepipe(t_mini *mini);

// tokenizer.c
t_token	*ft_tokenizer(char *input);
char	*ft_select_token(char *input, int *i);
t_token *listing_token(char **tmp);
int		input_size(char *input);

// tokenizing.c
t_token	*tokenizing_redirect(char **tmp, int *i);
t_token *tokenizing_pipe(char **tmp, int *i);
t_token *tokenizing_other(char **tmp, int *i);

// punct_handle.c
char 	*dollar_sign(char *input, int *i);
char 	*redirect_sign(char *input, int *i);
char 	*pipe_sign(char *input, int *i);

// lst_tok.c
t_token	*tok_lstnew(char **content, t_type data);
void	tok_lstadd_back(t_token **lst, t_token *new);
t_token	*tok_lstlast(t_token *lst);
int		is_splitted(char *tmp);

// lst_exe.c
t_exec	*exe_lstnew(t_token *tmp);
void	exe_lstadd_back(t_exec **lst, t_exec *new);
t_exec	*exe_lstlast(t_exec *lst);

// exec.c
void	ft_parse_exec(t_mini *mini);
void	ft_exec(t_mini *mini);
int		last_node(t_exec *cmd, t_mini *mini);
int		exec_node(t_exec *cmd, t_mini *mini);

// escape.c
int	escape_word(char *input, int *i);
int	escape_quote(char *input, int *i);
int	escape_redirect(char *input, int *i);

// builtin_exec.c
void	exec_builtins(char **cmd, t_mini *mini);

// builtins.c
void	ft_pwd(void);
void	ft_env(t_mini *mini);
void	ft_cd(char **cmd, t_mini *mini);
void	ft_exit(void);


#endif