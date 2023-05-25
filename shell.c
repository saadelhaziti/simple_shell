#include "main.h"

/**
 * env - prints the environment variables
 */

void env(void)
{

	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * shell-> the brain of mini shell
 */

void shell(void)
{
	char *line = NULL, *arg[10], *path = "/bin/", *full;
	size_t len = 0;
	ssize_t read;

	while ((read = read_cmd(&line, &len)) != -1)
	{

		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}
		if (line[0] == '\0')
		{
			continue;
		}

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		if (strcmp(line, "env") == 0)
		{
			env();
			free(line);
			exit(EXIT_SUCCESS);
		}

		tokenize(line, arg);

		_path(arg[0], path, &full);

		execute(arg, full, line);
	}

	free(line);
}
