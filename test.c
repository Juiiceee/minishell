#include "include/minishell.h"

/*typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;*/

/*void free_list_element(t_list **lst, t_list *element)
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
	while (prev->next && prev->next != element)
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

void	ft_env(t_mini *mini)
{
	t_list *str;

	str = mini->env;
	if (!mini->env)
		return ;
	while (str->next != NULL)
	{
	 	printf("%s\n", (char *)str->content);
		str = str->next;
	}
	printf("%s\n", (char *)str->content);
}*/

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

/*int main(int argc, char **argv, char **envp)
{
	t_mini mini;

	char *sa[] = {"coucou", "sa=lut", "feur", NULL};
	recoenv(&mini, envp);
}*/

#include <stdio.h>
#include <signal.h>
#define _GNU_SOURCE

void handler(int signum) {
    printf("Received signal: %d\n", signum);
	exit(0);
    // Retrieve more information from the siginfo_t structure if needed
}

int main() {
   	struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    printf("%d\n",sigaction(SIGINT, &sa, NULL));
	
	while (1)
		;
	
    // Rest of the code...
    return 0;
}
