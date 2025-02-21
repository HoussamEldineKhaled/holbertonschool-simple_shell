#include "shell.h"

/**
 * tokenize - malloc array and set token
 * @token: token
 * @array: array for token
 * @i: index
*/

void tokenize(char *token, char **array, int i)
{
while (token)
{
array[i] = token;
token = strtok(NULL, " \n");
i++;
}
array[i] = NULL;
}

/**
 * exec_cmd - execute command
 * @child: new process
 * @array: command
 * @status: execution status
*/
void exec_cmd(pid_t child, char **array, int status)
{
if (child == -1)
{
perror("Creation Failure");
exit(41);
}
if (child == 0)
{
if (execve(array[0], array, NULL) == -1)
{
perror("Execution Failure");
exit(97);
}
}
else
{
wait(&status);
}
}

/**
 * main - execute the shell loop
 * argc: argument count
 * argv: argument value
 * Return: 0
*/
int main(int argc, char *argv[])
{
char *buf = NULL;
char *token = NULL;
char **array = NULL;
size_t count = 0;
ssize_t nread;
pid_t child;
int i = 0, status = 0;
(void)argc, (void)argv;
while (1)
{
write(STDOUT_FILENO, "$ ", 2);
nread = getline(&buf, &count, stdin);
if (nread == -1)
{
write(STDOUT_FILENO, "\n", 2);
free(buf);
exit(1);
}
token = strtok(buf, "\n");
array = malloc(sizeof(char*) * 1024);
i = 0;
tokenize(token, array, i);
child = fork();
exec_cmd(child, array, status);
printf("%s", buf);
}
free(buf);
return (0);
}
