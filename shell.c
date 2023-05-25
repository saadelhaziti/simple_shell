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


	while (1)
	{
		read = read_cmd(&line, &len);

		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}
		if (line[0] == '\0')
		{
			continue;
		}

		if (strcmp(line, "exit\n") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		if (strcmp(line, "env\n") == 0)
		{
			env();
		}


		tokenize(line, arg);

		_path(arg[0], path, &full);

		execute(arg, full);

	}

	free(line);
}
