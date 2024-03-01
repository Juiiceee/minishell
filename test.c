#include "include/minishell.h"

/*typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;*/

void free_list_element(t_list **lst, t_list *element)
{
	t_list	*prev;
	if (!*lst || !element)
		return;
	if (*lst == element)
	{
		*lst = element->next;
		free(element);
		return;
	}
	prev = *lst;
	while (!prev->next && prev->next != element)
		prev = prev->next;
	if (prev->next == element)
	{
		prev->next = element->next;
		free(element);
	}
}

void	unset(t_mini *mini, char *find)
{
	int	check;
	t_list *st;
	char	*tmp;
	st = mini->env;
	check = 1;
	if (!st || !st->content)
		return ;
	tmp = ft_strjoin(find, "=");
	while (check && st->next)
	{
		check = ft_strncmp(tmp, (char *)st->content, ft_strlen(tmp));
		if (check == 0)
			break ;
		st = st->next;
	}
	check = ft_strncmp(tmp, (char *)st->content, ft_strlen(tmp));
	if (check == 0)
		free_list_element(&mini->env, st);
	return ;
}

/*void	ft_env(t_list *lst)
{
	t_list	*st;

	st = lst;
	if (!st)
		return ;
	while (st)
	{
		printf("%s\n",(char *)st->content);
		st = st->next;
	}
}*/

int main(int argc, char **argv, char **envp)
{
	t_mini mini;

	char *sa[] = {"coucou", "sa=lut", "feur", NULL};
	recoenv(&mini, sa);
	//t_list	*st = mini.env->next;
	unset(&mini, "sa");
	printf("%s", (char *)mini.env->next->content);
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
