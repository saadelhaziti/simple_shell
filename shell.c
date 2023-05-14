#include "main.h"

/**
 * shell-> the brain of mini shell
 */

void shell(void)
{
	char *line = NULL, *arg[10], *tock;
	int i = 0, pid;
	size_t len = 0;
	ssize_t read;

	write(1, "($)", 3);
	read = getline(&line, &len, stdin);
	while (read != -1)
	{
		for (tock = strtok(line, " \t\n\"\'\\#&*`"), i = 0; tock != NULL;
				tock = strtok(NULL, " \t\n\"\'\\#&*`"), i++)
		{
			arg[i] = tock;
		}
		arg[i] = NULL;

		pid = fork();
		if (pid == 0)
		{
			if (execve(arg[0], arg, NULL) == -1)
			{
				perror("./shell");
				break;
			}
		}
		else
		{
			wait(NULL);
			write(1, "($)", 3);
			read = getline(&line, &len, stdin);
		}
	}
	free(line);
}
