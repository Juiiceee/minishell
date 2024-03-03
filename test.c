#include "include/minishell.h"

int	echo()
{
	printf("COUCOU");
	return (15);
}

void	truc()
{
	return ((void)echo());
}

int main(int argc, char **argv, char **envp)
{
	truc();
	/*pid_t	pid;
	int	status;
	char *sa[] = {"/bin/cat", "dsdasd", NULL};

	pid = fork();
	if (pid == 0)
	{
		execve(sa[0], sa, envp);
	}
	waitpid(pid, &status, 0);
	printf("%d", WEXITSTATUS(status));
	return 0;*/
}
