#include "main.h"

/**
 * read_cmd -> reads the user input from stdin
 *
 * @line: input
 * @len: input
 *
 * Return: line
 */

ssize_t read_cmd(char **line, size_t *len)
{
	write(1, "($) ", 4);
	return (getline(line, len, stdin));
}

/**
 * tokenize -> splits a command line into individual arguments
 *
 * @line: input
 * @arg: input
 *
 * Return: number of arguments
 */

int tokenize(char *line, char **arg)
{
	int i;
	char *tock;

	for (tock = strtok(line, " \t\n\"\'\\#&*`"), i = 0; tock != NULL;
			tock = strtok(NULL, " \t\n\"\'\\#&*`"), i++)
	{
		arg[i] = tock;
	}
	arg[i] = NULL;
	return (i);
}
