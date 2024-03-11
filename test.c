#include "include/minishell.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	char *cmd[] = {"ls", NULL};
	execve("ls", cmd, envp);
}
