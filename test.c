#include "include/minishell.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*int is_regular_file(const char *path) {
	struct stat sa;
	if (lstat(path, &sa) == 0) {
		if (S_ISREG(sa.st_mode)) {
			return 1; // It's a regular file
		}
	}
	return 0; // It's not a regular
}

int main(int argc, char **argv, char **envp) {
	if (is_regular_file("a.out")) {
		printf("oui");
	}
	return 0;
}*/

int main(int argc, char **argv, char **envp)
{
	struct stat sa;

	lstat("valgrind", &sa);
	if (S_ISDIR(sa.st_mode))
		printf("oui");
}
