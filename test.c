#include "include/minishell.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void free_list_element(t_list **lst, t_list *element)
{
    if (*lst == NULL || element == NULL)
        return;
    
    if (*lst == element)
    {
        *lst = element->next;
        free(element);
        return;
    }
    
    t_list *prev = *lst;
    while (prev->next != NULL && prev->next != element)
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
	int	lenght;
	t_list *st;

	st = mini->env;
	check = 1;
	if (!st || !st->content || ft_strlen(find) == 0)
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

void	ft_env(t_list *lst)
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
}

int main(int argc, char **argv, char **envp)
{
	t_mini mini;

	recoenv(&mini, envp);
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
