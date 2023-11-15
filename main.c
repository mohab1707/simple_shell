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
 * simple_shell.
 *
 * Return: Always 0.
 */
int main(void)
{
char buffer[BUFFER_SIZE];
int status;
pid_t pid;
int i;
 char *args[BUFFER_SIZE];
while (1)
{
printf("#cisfun$ ");
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
pid = fork();
if (pid == -1)
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
if (execve(args[0], args, NULL) == -1)
{
perror("./shell");
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
}
return (0);
}
