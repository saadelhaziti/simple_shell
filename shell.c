#include "main.h"

int bintest(char *bin)
{
    char *test = "/bin/";
    while (*test != '\0')
    {
        if (*test != *bin)
        {
            return 0;
        }
        test = test + 1;
        bin = bin + 1;
    }
    return 1;
}

/**
 * shell-> the brain of mini shell
 */

void shell(void)
{
    char *line = NULL, *arg[10], *tock, *path = "/bin/", *full;
    int i = 0, pid, len2 = 0;
    size_t len = 0;
    ssize_t read;

    write(1, "($) ", 4);
    read = getline(&line, &len, stdin);
    while (read != -1)
    {
        if (strcmp(line, "exit\n") == 0)
		{
			exit(EXIT_SUCCESS);
		}
        
        for (tock = strtok(line, " \t\n\"\'\\#&*`"), i = 0; tock != NULL;
             tock = strtok(NULL, " \t\n\"\'\\#&*`"), i++)
        {
            arg[i] = tock;
        }
        arg[i] = NULL;
        if (bintest(arg[0]) == 1)
        {
            len2 = 1 + strlen(arg[0]);
            full = (char *)malloc(sizeof(char) * len2);
            strcpy(full, arg[0]);
        }
        else
        {
            switch (arg[0][0])
            {
            case '.':
            case '/':
                len2 = 1 + strlen(arg[0]);
                full = (char *)malloc(sizeof(char) * len2);
                strcpy(full, arg[0]);
                break;

            default:
                len2 = strlen(path) + 2 + strlen(arg[0]);
                full = (char *)malloc(sizeof(char) * len2);

                strcpy(full, path);
                strcat(full, arg[0]);

                break;
            }
        }

        pid = fork();
        if (pid == 0)
        {
            if (execve(full, arg, NULL) == 1)
            {
                perror("./shell");
                break;
            }
        }
        else
        {
            wait(NULL);
            write(1, "($) ", 4);
            read = getline(&line, &len, stdin);
            free(full);
        }
    }
    free(line);
}
