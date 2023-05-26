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
 * isnum - check if number
 * @str: string
 * Return: 1 if number 0 otherwise
 */
int isnum(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}
/**
 * handle_exit - handle exit
 * @arg: arg array
 * @line: command user
 * @exitstatus: the exit status
 * Return: void
 */
void handle_exit(char *arg[], char *line, int exitstatus)
{
	int i = 0;
	char *error = "./hsh: 1: exit: Illegal number: ";

	if (arg[1])
	{
		if (arg[1][0] != '-' && isnum(arg[1]))
			exitstatus = atoi(arg[1]);
		else
		{
			while (error[i])
			{
				write(STDERR_FILENO, &error[i], 1);
				i++;
			}
			i = 0;
			while (arg[1][i])
			{
				write(STDERR_FILENO, &arg[1][i], 1);
				i++;
			}
			write(STDERR_FILENO, "\n", 1);
			exitstatus = 2;
		}
	}
	else if (exitstatus == -1)
		exitstatus = EXIT_SUCCESS;
	free(line);
	exit(exitstatus);
}
/**
 * shell - the shell
 */
void shell(void)
{
	char *line = NULL, *arg[10], *path = "/bin/", *full;
	size_t len = 0;
	ssize_t read;
	int exitstatus = -1;

	while ((read = read_cmd(&line, &len)) != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		if (line[0] == '\0')
			continue;
		if (trim_input(line))
			break;
		if (strcmp(line, "env") == 0)
		{
			env();
			free(line);
			exit(EXIT_SUCCESS);
		}
		tokenize(line, arg);
		if (strcmp(arg[0], "exit") == 0)
			handle_exit(arg, line, exitstatus);
		_path(arg[0], path, &full);
		exitstatus = execute(arg, full, line);
	}
	free(line);
}
