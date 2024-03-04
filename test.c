#include "include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	int	i = 0;
	char str[] = "123";
	while (str[i])
	{
		if (!ft_isdigit(*str))
		{
			printf("non");
			exit(2);
		}
		i++;
	}
	printf("oui");
}
