#include "main.h"

/**
 * bintest -> checks whether an executable path belongs to /bin/
 *
 * @bin: input
 *
 * Return: 1 on success and 0 on failure
 */

int bintest(char *bin)
{
	char *test = "/bin/";

	while (*test != '\0')
	{
		if (*test != *bin)
		{
			return (0);
		}
		test = test + 1;
		bin = bin + 1;
	}
	return (1);
}


/**
 * _path -> constructs a full path for an executable
 *
 * @bin: input
 * @path: input
 * @full: input
 *
 */

void _path(char *bin, char *path, char **full)
{
	int len2;

	if (bintest(bin))
	{
		len2 = 1 + strlen(bin);
		*full = (char *)malloc(sizeof(char) * len2);
		strcpy(*full, bin);
	}
	else
	{
		switch (bin[0])
		{
			case '.':
			case '/':
				len2 = 1 + strlen(bin);
				*full = (char *)malloc(sizeof(char) * len2);
				strcpy(*full, bin);
				break;

			default:
				len2 = strlen(path) + 2 + strlen(bin);
				*full = (char *)malloc(sizeof(char) * len2);

				strcpy(*full, path);
				strcat(*full, bin);

				break;
		}
	}
}
