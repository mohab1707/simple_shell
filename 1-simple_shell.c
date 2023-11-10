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
 * simple_shell 0.1.
 *
 * Return: Always 0.
 */
int main(void)
{
char buffer[BUFFER_SIZE];
int status;
pid_t pid;
char *args[2];
while (1)
{
printf("#cisfun$ ");
if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
{
break;
}
buffer[strcspn(buffer, "\n")] = '\0';
pid = fork();
if (pid == -1)
{
perror("Fork failed");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
args[0] = buffer;
args[1] = NULL;
if (execve(buffer, args, NULL) == -1)
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
printf("%s: not found\n", buffer);
}
}
}
return (0);
}
