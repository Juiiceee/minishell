#include "include/minishell.h"
#include <stdint.h>
#include <stdio.h>

int	ft_checkt(char **cmd, t_mini *mini, size_t j)
{
	size_t	i;

	i = 0;
	//if (cmd[j][0] == '=')
	while (cmd[j][i] != '=' && cmd[j][i])
	{
		if (!ft_isalpha(cmd[j][i]))
		{
			mini->exitstatus = 1;
			return ((void)printf("`%s': not a valid identifier", ft_substr(cmd[j], 0, ++i)), 1);
		}
		i++;
	}
	if (isdigit(cmd[j][0]))
	{
		mini->exitstatus = 1;
		return ((void)printf("`%s': not a valid identifier", ft_substr(cmd[j], 0, i)), 1);
	}
	if (!ft_strchr(cmd[j], '='))
		return (1);
	return (0);
}

void	ft_xit(t_mini *mini, char **cmd)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 1;
	if (!cmd[1])
		return ((void)printf("EWEW"));
	while (cmd[j])
	{
		if (ft_checkt(cmd, mini, j))
			return ;
		while (cmd[j][i] != '=' && cmd[j][i])
			i++;
		if (cmd[j][0] != '=' && ft_strchr(cmd[j], '=') && ft_strlen(cmd[j]) != i)
			printf("ca export");
		i = 0;
		j++;
	}
	//refreshtab(
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	char *sa[] = {"export", "=salut", NULL};
	ft_xit(&mini, sa);
}
