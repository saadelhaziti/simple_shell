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
 * trim_input - trim string
 * @str: string to be trimmed
 * Return: 1 if there only space or tab in string otherwise 0
 */
int trim_input(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	}
	return (1);
}
/**
 * shell - the shell
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
		if (trim_input(line))
		{
			break;
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
