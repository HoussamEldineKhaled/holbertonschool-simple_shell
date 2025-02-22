#include "shell.h"
/**
 * tokenize - malloc array and set token
 * @array: array for token
 * @i: index
 * @buf: buffer
*/
void tokenize(char **array, int i, char *buf)
{
char *token;
token = strtok(buf, " \n");
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
void exec_cmd(pid_t child, char **array, int status, char *path, char *buf)
{
if (child == -1)
{
perror("Creation Failure");
free(buf);
free(array);
free(path);
exit(41);
}
if (child == 0)
{
if (execve(path, array, NULL) == -1)
{
perror("Execution Failure");
free(buf);
free(array);
free(path);
exit(97);
}
}
else
{
wait(&status);
if (WIFEXITED(status))
{
exit(WEXITSTATUS(status));
}
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
char *buf = NULL, *path = NULL;
char **array = NULL;
size_t count = 0;
ssize_t nread;
pid_t child;
int i = 0, status = 0;
(void)argc, (void)argv;
while (1)
{
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "$ ", 2);
}
if (buf != NULL)
{
free(buf);
buf = NULL;
count = 0;
}
nread = getline(&buf, &count, stdin);
if (nread == -1)
{
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "\n", 2);
}
free(buf);
exit(1);
}
if (buf[nread - 1] == '\n')
{
buf[nread - 1] = '\0';
}
if (nread > 0 && buf[nread - 1] == '\n')
{
buf[nread - 1] = '\0';
}
array = malloc(sizeof(char*) * 1024);
if (array == NULL)
{
perror("malloc failure");
free(buf);
exit(EXIT_FAILURE);
}
i = 0;
tokenize(array, i, buf);
if (array[0] == NULL)
{
free(array);
continue;
}
path = get_file_path(array[0]);
if (path == NULL)
{
printf("Command not found: %s\n", array[0]);
free(array);
continue;
}
child = fork();
exec_cmd(child, array, status, path, buf);
free(array);
free(path);
}
free(buf);
return (0);
}
