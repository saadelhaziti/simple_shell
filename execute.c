#include "main.h"

/**
 * execute -> forks a child process and runs the specified command
 *
 * @arg: input
 * @full: input
 * @line: input
 */

void execute(char **arg, char *full, char *line)
{
	int pid = fork();

	if (pid == 0)
	{
		if (execve(full, arg, NULL) == -1)
		{
			free(full);
			free(line);
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
		free(full);
	}
}
