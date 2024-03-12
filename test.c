#include "include/minishell.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)
{
	char *sa[] = {"./sa.sh", NULL};
	int i = execve(sa[0], sa, envp);
	perror("execve");
	return (i);
}
