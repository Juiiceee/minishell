#include "include/minishell.h"

int	recoenv(t_mini *mini, char **argv)
{
	int	i;

	mini->env = NULL;
	i = 0;
	if (!argv)
		return (1);
	while (argv[i])
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup(argv[i++])));
	return (0);
}

/*char	**lsttotab(t_mini *mini)
{
	int	i;
	char	**tab;
	t_list	*st;
	t_list	*lst;

	st = mini->env;
	lst = mini->env;
	i = 0;
	tab = malloc((sizeof(char *) * (ft_lstsize(lst) + 1)));
	if (!tab)
		return (NULL);
	while (st)
	{
		tab[i] = ft_strdup((char *)st->content);
		i++;
		st = st->next;
	}
	tab[i] = NULL;
	return (tab);
}*/

char	*pathenv(t_mini *mini, char *find)
{
	int	check;
	int	lenght;
	t_list *st;

	st = mini->env;
	check = 1;
	if (!st || !st->content)
		return (NULL);
	lenght = ft_strlen(find);
	if (!ft_strncmp(find, (char *)st->content, lenght))
		return ((char *)st->content + (lenght + 1));
	while (check && st)
	{
		st = st->next;
		check = ft_strncmp(find, (char *)st->content, lenght);
	}
	if (check == 0)
		return ((char *)st->content + (lenght + 1));
	return (NULL);
}

void	modifievaluelst(t_list **st, char *find, char *new)
{
	char	*tmp;
	t_list	*lst;

	lst = *st;
	free(lst->content);
	if (ft_strlen(new) == 0)
		lst->content = ft_strjoin(find, "=");
	else
	{
		tmp = ft_strjoin(find, "=");
		lst->content = ft_strjoin(tmp, new);
		free(tmp);
	}
	return ;
}

void	addvaluelst(t_mini *mini, char *find, char *new)
{
	char	*tmp;
	char	*tmp1;

	tmp = ft_strjoin(find, "=");
	if (ft_strlen(new) == 0)
		ft_lstadd_back(&mini->env, ft_lstnew(tmp));
	else
	{
		tmp1 = ft_strjoin(tmp, new);
		ft_lstadd_back(&mini->env, ft_lstnew(tmp1));
		free(tmp1);
	}
	free(tmp);
}

void	lstchangevalue(t_mini *mini, char *find, char *new)
{
	int	check;
	int	lenght;
	t_list *st;

	st = mini->env;
	check = 1;
	if (!st || !st->content)
		return ;
	lenght = ft_strlen(find);
	if (!ft_strncmp(find, (char *)st->content, lenght))
	{
		modifievaluelst(&st, find, new);
		return ;
	}
	while (check && st)
	{
		st = st->next;
		check = ft_strncmp(find, (char *)st->content, lenght);
	}
	if (check == 0)
	{
		modifievaluelst(&st, find, new);
		return ;
	}
	addvaluelst(mini, find, new);
}

void	refreshtab(t_mini *mini)
{
	if (mini->tabenv)
		freetab(mini->tabenv);
	lsttotab(mini);
	if (!mini->tabenv)
		return ;
}

int main(int argc, char **argv, char **envp)
{
	t_mini mini;
	char *oui;

	char *sa[] = {"cou=sasacou", "fe=sasaur", "PATH=/home/lbehr/bin:/home/lbehr/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
	recoenv(&mini, sa);
	//printf("|%s|\n", pathenv(&mini, "cou"));
	lsttotab(&mini);
	printf("tab avant =|%s| \n", mini.tabenv[0]);
	lstchangevalue(&mini, "cou", "");
	refreshtab(&mini);
	printf("tab apres =|%s| \n", mini.tabenv[0]);
	printf("lst apres =|%s|", (char *)mini.env->content);
	//ft_lstfree(mini.env);
	freelst(mini.env);
	freetab(mini.tabenv);
	/*pid_t	pid = fork();
	printf("avant%s\n", getcwd(NULL, 0));
	char *oui[] = {"/bin/cd", ""}
	if (pid == 0)
	{
		//chdir(getenv("HOME"));
		
		printf("dans l'enfant %s\n", getcwd(NULL, 0));
		exit(0);
	}
	waitpid(pid, NULL, 0);
	printf("apres %s\n", getcwd(NULL, 0));*/
}
/*
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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content)
{
	t_list	*newlst;

	newlst = malloc(sizeof (*newlst));
	if (!newlst)
		return (NULL);
	newlst->content = content;
	newlst->next = NULL;
	return (newlst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (*lst)
	{
		last->next = new;
	}
	else
		*lst = new;
}

int	recoenv(t_mini *mini, char **argv)
{
	int	i;

	mini->env = NULL;
	i = 0;
	if (!argv)
		return (1);
	while (argv[i])
		ft_lstadd_back(&mini->env, ft_lstnew(ft_strdup((char *)argv[i++])));
	return (0);
}
int main()
{
	char *sa[] = {"cou=sasacou", "fe=sasaur", "PATH=/home/lbehr/bin:/home/lbehr/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin", NULL};
	recoenv(&mini, sa);
}


*/