#include "../include/minishell.h"

int	tablength(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

int	recoenv(char **argv, t_mini *mini)
{
	int	length;

	length = tablength(argv);
	if (!length)
		return (1);
	
	while (argv)
	{
		ft_strdup()
	}
}

#define buffersize 1024

int main(int argc, char **argv, char **env)
{
	t_mini mini;
	char hello[buffersize];
	char buf[1024];
	int	running;

	recoenv(env, &mini);
	printf("%s", mini.env[3]);
	/*running = 1

	while (running)
	{
		if (!getcwd(hello, sizeof(hello)))
			perror("getcwd");
		write(1, &hello, ft_strlen(hello));
		read(0, buf, buffersize);
		if (!buf)
			continue;
		else
			
		printf("%s\n", buf);
	}*/

	/*pid_t	pid;
	read(0, &hello, 500);
	printf("\n<minishell>: %s", hello);
	if (getcwd(hello,sizeof(hello)))
	{
		printf("Current dir : %s", hello);
	}
	else {
        perror("getcwd() error");
        return 1;
	}
	if (chdir("../") < 0) {
        perror("chdir() error");
        return 1;
    }
	if (getcwd(hello,sizeof(hello)))
	{
		printf("\nCurrent dir : %s\n", hello);
	}
	else {
        perror("getcwd() error");
        return 1;
	}
	
	char *cmd[] = {"/bin/ls", NULL};
	pid = fork();
	if (pid == 0)
	{
		execve(cmd[0], cmd, env);
	}
	waitpid(pid, NULL, 0);*/
	/*while (1)
	{
		write(1, &hello[i], 1);
		i++;
	}*/
}