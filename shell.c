#include "main.h"


/**
 * shell-> the brain of mini shell
 */

void shell(void)
{
	char *line = NULL, *arg[10], *path = "/bin/", *full;
	size_t len = 0;
	ssize_t read;

	read = read_cmd(&line, &len);
	while (read != -1)
	{
		if (strcmp(line, "exit\n") == 0)
		{
			exit(EXIT_SUCCESS);
		}

		tokenize(line, arg);

		_path(arg[0], path, &full);

		execute(arg, full);

		read = read_cmd(&line, &len);
	}

	free(line);
}
