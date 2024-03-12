#include "include/minishell.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

/*int main(int argc, char **argv, char **envp)
{
	char *sa[] = {"./sa.sh", NULL};
	int i = execve(sa[0], sa, envp);
	perror("execve");
	return (i);
}*/
