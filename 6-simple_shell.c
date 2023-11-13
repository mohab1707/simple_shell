#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * _getline - Custom getline function
 *
 * Return: Pointer to the line read or
 * NULL on failure or end of file.
 */
char *_getline(void)
{
static char buffer[BUFFER_SIZE];
int c;
int i = 0;
while ((c = getchar()) != EOF && c != '\n')
{
buffer[i++] = c;
if (i >= BUFFER_SIZE - 1)
{
break;
}
}
buffer[i] = '\0';
if (i == 0 && c == EOF)
{
return (NULL);
}
return (buffer);
}

/**
 * main - Entry point of the shell program
 * (Simple Shell 0.1)
 *
 * Return: Always 0.
 */
int main(void)
{
char *buffer;
int status;
pid_t pid;
char *args[2];
while (1)
{
printf("#cisfun$ ");
buffer = _getline();
if (buffer == NULL)
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
perror("./shell ");
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
