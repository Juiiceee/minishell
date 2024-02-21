#include <unistd.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define buffersize 1024

int main(int argc, char **argv, char **env)
{
	char hello[buffersize];
	char buf[1024];
	int	running;

	running = 1;

	while (running)
	{
		if (!getcwd(hello, sizeof(hello)))
			perror("getcwd");
		write(1, &hello, ft_strlen(hello));
		read(0, buf, buffersize);
		/*if (!buf)
			continue;
		else
			*/
		printf("%s\n", buf);
	}

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