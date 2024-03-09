#include "include/minishell.h"

void	oui(int	*i)
{
	(*i)++;
}

int main(int argc, char **argv, char **envp)
{
	int i = 0;
	oui(&i);
	printf("%d", i);
}
