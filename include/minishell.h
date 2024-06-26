/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:13:45 by lbehr             #+#    #+#             */
/*   Updated: 2024/04/29 13:47:37 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef enum e_type
{
	CMD,
	IN_REDIRECT,
	OU_REDIRECT,
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
	char			**global;
	t_type			data_type;
	struct s_token	*next;
}	t_token;

typedef struct s_exec
{
	char			**cmd;
	char			**in;
	int				fdin;
	int				is_fdin;
	char			**out;
	int				fdout;
	int				is_fdout;
	int				builtin;
	struct s_exec	*next;
}	t_exec;

typedef struct s_mini
{
	char		*currentpath;
	struct stat	dossier;
	char		*userstr;
	char		*user;
	char		*input;
	t_list		*env;
	uint8_t		exitstatus;
	char		**tabenv;
	char		**tabcmd;
	int			exe_n;
	int			exe_size;
	pid_t		*pid;
	int			*pipe;
	int			pipe_n;
	int			clear_fd[2];
	t_token		*lst;
	t_exec		*exe;
}	t_mini;

// utilstab.c
int				tablength(char **tab);
void			lsttotab(t_mini *mini);
void			refreshtab(t_mini *mini);
int				ft_lstsizestrchr(t_list *lst, char c);
int				ft_isspace(int c);

// free.c
void			freetab(char **tab);
void			freelst(t_list *lst);
void			free_list_element(t_list **lst, t_list *element);
void			child_clean_exit(t_mini *mini, int ext_code);
void			clean_for_exit(t_mini *mini, int ext_code);

// env.c
int				recoenv(t_mini *mini, char **argv);
int				recocp(t_mini *mini);

// init.c
int				init(t_mini *mini, char **env);

// prompt.c
char			*pathenv(t_mini *mini, char *find);
int				recouser(t_mini *mini);

// running.c
int				checkisdir(t_mini *mini);
void			running(t_mini *mini);
void			createprename(t_mini *mini);
int				insiderunning(t_mini *mini);

// signal.c
void			recosignal(void);
void			recosigint(int sig);

// export.c
void			modifievaluelst(t_list **st, char *find, char *new);
void			addvaluelst(t_mini *mini, char *find, char *new);
void			export(t_mini *mini, char *find, char *new);
int				ft_checkexport(char **cmd, t_mini *mini, size_t j);
void			exportsolo(t_mini *mini);

// cd.c
int				execcd(t_mini *mini, char *path);

// parse_line.c
char			*squote_parse(char *input, int *index);
char			*dquote_parse(char *input, int *index, t_mini *mini);
char			*str_parse(char *input, int *index);
char			*punct_parse(char *input, int *i, t_mini *mini, int *j);

// utils.c
char			*free_and_join(char *old, char *new);
char			**ft_subtab(char **tab, int start, int len);
int				ft_tablen(char **tab);
int				ft_strcmp(char *s1, char *s2);

// tokenizer.c
t_token			*ft_tokenizer(char *input, t_mini *mini);
char			*ft_select_token(char *input, int *i, t_mini *mini, int *j);
t_token			*listing_token(char **tmp);
int				input_size(char *input, t_mini *mini);
char			*split_env(char *old, char **tmp, int *j);

//utilsexport.c
void			exportvalueseul(t_mini *mini, char *find);
void			freesub(t_mini *mini, char **cmd, size_t j, size_t	i);
int				ft_alphaunderscore(char c);
void			printexe(int i, char *str);
void			printflu(int i, char *str);

// tokenizing.c
t_token			*tokenizing_redirect(char **tmp, int *i);
t_token			*tokenizing_pipe(char **tmp, int *i);
t_token			*tokenizing_other(char **tmp, int *i);

// punct_handle.c
char			*dollar_sign(char *input, int *i, t_mini *mini);
char			*redirect_sign(char *input, int *i);
char			*pipe_sign(char *input, int *i);

// lst_tok.c
t_token			*tok_lstnew(char **content, t_type data);
void			tok_lstadd_back(t_token **lst, t_token *new);
t_token			*tok_lstlast(t_token *lst);
int				is_splitted(char **tmp, int *i);

// lst_exe.c
t_exec			*exe_lstnew(t_token *tmp);
void			exe_lstadd_back(t_exec **lst, t_exec *new);
t_exec			*exe_lstlast(t_exec *lst);

// exec.c
void			ft_parse_exec(t_mini *mini);
void			ft_exec(t_mini *mini);
int				parsingcommand(t_exec *cmd, t_mini *mini);
int				exec_node(t_exec *cmd, t_mini *mini);

// escape.c
int				escape_word(char *input, int *i, t_mini *mini);
int				escape_quote(char *input, int *i);
int				escape_redirect(char *input, int *i);

// builtin_exec.c
void			exec_builtins(t_exec *exec, t_mini *mini);

// builtins.c
void			ft_pwd(t_mini *mini);
void			ft_env(t_mini *mini);
void			ft_cd(char **cmd, t_mini *mini);
void			ft_exit(t_mini *mini, char **cmd);
void			ft_export(char **cmd, t_mini *mini);

// builtins2.c
void			ft_unset(char **cmd, t_mini *mini);
void			ft_echo(char **cmd, t_mini *mini);

//unset.c
void			unset(t_mini *mini, char *find);

// lst_free.c
void			ft_tokclear_str(t_token **lst);
void			ft_execlear(t_exec **lst, void (*del)(char **));
void			ft_tokclean(t_token **lst);
void			ft_envclean(t_list **lst);

// here_doc.c
int				heredoc(char *limiter, t_mini *mini);

// redirect.c
int				input(t_mini *mini, t_exec *exec);
int				output(t_mini *mini, t_exec *exec);
void			parse_redirect_out(t_token *tmp, t_exec *newlst);
void			parse_redirect_in(t_token *tmp, t_exec *newlst);

// utils2.c
char			*sub_and_free(char *old, int from, int to);
char			*free_old_and_join(char *old, char *new);
char			*free_new_and_join(char *old, char *new);
char			*cut_first_char(char *old);
char			**ft_tabjoin(char **s1, char **s2);

// lst_utlis.c
int				ft_exesize(t_exec *lst);

// pipe_utils.c
void			init_pipe(t_mini *mini);
void			closepipe(t_mini *mini);

// utilsexec.c
int				what_is_error(t_exec *cmd, t_mini *mini, int *status);
void			free_child(t_mini *mini);
int				utilsparsingcom(char **envpath, int *i, t_exec *cmd);
void			utilsexec_node(t_exec *cmd, t_mini *mini);
int				utilsft_exec(t_mini *mini, t_exec *tmp_exe);

// validation.c
int				input_validation(t_mini *mini);
void			free_inpt_error(t_mini *mini);
int				exec_validation(t_mini *mini);

// exit_status.c
void			child_exit_signal(t_mini *mini, int status);

// utilsexit.c
void			utilsexit(t_mini *mini, char **cmd);

// var_dquote.c
char			*var_dquote(char *tmp, t_mini *mini, int *index);

#endif