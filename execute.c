#include "main.h"

/**
 * execute -> forks a child process and runs the specified command
 *
 * @arg: input
 * @full: input
 * @line: input
 * Return: exit status of fork
 */

int execute(char **arg, char *full, char *line)
{
	int pid = fork();
	int status = 0;
	int fork_status = 0;

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
		wait(&status);
		free(full);
		if (WIFEXITED(status))
			fork_status = WEXITSTATUS(status);
	}
	return (fork_status);
}
