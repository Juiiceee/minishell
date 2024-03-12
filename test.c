#include "include/minishell.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>

int	checkisdir(t_mini *mini)
{
	mini->dossier.st_mode = 0;
	if (!mini->lst->next)
	{
		if (!ft_strncmp(mini->lst->global[0], "./", 2)
			|| !ft_strncmp(mini->lst->global[0], "/", 1))
		{
			lstat(mini->lst->global[0], &mini->dossier);
			if (S_ISDIR(mini->dossier.st_mode))
				return (printf("%s: Is a directory\n", mini->lst->global[0]),
					mini->exitstatus = 126, 1);
		}
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	t_mini	mini;
	char sa[] = "valgrind";

	lstat(sa, &mini.dossier);
	if (S_ISDIR(mini.dossier.st_mode))
		return (printf("%s: Is a directory\n", sa),
			mini.exitstatus = 126, 1);
}
