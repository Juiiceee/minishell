#include "../include/minishell.h"

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
