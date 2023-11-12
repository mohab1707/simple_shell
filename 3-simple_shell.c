#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * main - Entry point of the shell program
 *
 * simple_shell 0.3.
 *
 * Return: Always 0.
 */
int main(void)
{
    char buffer[BUFFER_SIZE];
    char *args[BUFFER_SIZE];
    int i;
    int status;
    pid_t pid;
    char *path;
    char *path_copy;
    char *token;
    char *full_path;
    int command_found;

    while (1)
    {
        printf(":) ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
        {
            break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';

        args[0] = strtok(buffer, " ");
        i = 0;

        while (args[i] != NULL)
        {
            i++;
            args[i] = strtok(NULL, " ");
        }

        path = getenv("PATH");
        path_copy = strdup(path);
        token = strtok(path_copy, ":");
        command_found = 0;

        while (token != NULL)
        {
            full_path = malloc(strlen(token) + strlen(args[0]) + 2);

            if (full_path == NULL)
            {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            sprintf(full_path, "%s/%s", token, args[0]);

            if (access(full_path, F_OK) != -1)
            {
                command_found = 1;
                break;
            }

            free(full_path);
            token = strtok(NULL, ":");
        }

        free(path_copy);

        if (command_found)
        {
            printf("Executing: %s\n", full_path);

            pid = fork();

            if (pid == -1)
            {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            }
            else if (pid == 0)
            {
                if (execve(full_path, args, NULL) == -1)
                {
                    perror("Execve failed");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                wait(&status);

                if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
                {
                    printf("%s: not found\n", args[0]);
                }
            }

            free(full_path);
        }
        else
        {
            printf("%s: not found\n", args[0]);
        }
    }

    return 0;
}
