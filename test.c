#include "include/minishell.h"

void	heredoc(char *limiter)
{
	int		heredoc;
	char	*line;
	char	*tmp;

	unlink(".heredoc");
	heredoc = open(".heredoc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!heredoc)
		return ((void)perror("open heredoc"));
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, limiter, ft_strlen(limiter)))
			break;
		tmp = ft_strjoin(line, "\n");
		write(heredoc, tmp, ft_strlen(tmp));
		free(tmp);
	}
	close(heredoc);
}

int main(int argc, char **argv, char **envp)
{
	heredoc("eof");
}
