#include "../include/minishell.h"

int	recoenv(char **argv, t_mini *mini)
{
	int	length;
	int	i;

	length = tablength(argv);
	i = 0;
	if (!length)
		return (1);
	mini->env = ft_calloc(sizeof(char *), length + 1);
	if (!mini->env)
		return (1);
	while (argv[i])
	{
		mini->env[i] = ft_strdup(argv[i]);
		if (!mini->env[i])
			return (1);
		i++;
	}
	mini->env[i] = NULL;
	return (0);
}

#define buffersize 1024

int main(int argc, char **argv, char **env)
{
	t_mini mini;
	char hello[buffersize];
	char buf[1024];
	int	running;

	if (recoenv(env, &mini))
		return (1);
	printf("normal : %s\nle miens : %s\n", env[0], mini.env[0]);
	freetab(mini.env);
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