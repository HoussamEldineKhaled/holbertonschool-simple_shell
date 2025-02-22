#include "shell.h"
/**
 * free_resources - free array resources
 * @array: array
 * @buf: buffer
 * @path: file path
*/
void free_resources(char **array, char **buf, char **path)
{
int i = 0;
if (array)
{
while (array[i])
{
free(array[i]);
array[i] = NULL;
i++;
}
}
if (buf && *buf)
{
free(*buf);
*buf = NULL;
}
if (path && *path)
{
free(*path);
*path = NULL;
}
}





/**
 * tokenize - malloc array and set token
 * @array: array for token
 * @i: index
 * @buf: buffer
*/
void tokenize(char ***array, char *buf)
{
char *token;
int i = 0;
int size = 64;
*array = malloc(sizeof(char*) * size);
if (!*array)
{
perror("malloc failure");
free(buf);
exit(EXIT_FAILURE);
}
token = strtok(buf, " \n");
if (!token)
{
free(*array);
*array = NULL;
return;
}
while (token)
{
if (i >= size - 1)
{
size *= 2;
*array = realloc(*array, sizeof(char*) * size);
if (!*array)
{
perror("realloc failed");
exit(EXIT_FAILURE);
}
}
(*array)[i] = strdup(token);
if (!(*array)[i])
{
perror("strdup failed");
free_resources(*array, NULL, NULL);
exit(EXIT_FAILURE);
}
token = strtok(NULL, " \n");
i++;
}
(*array)[i] = NULL;
}





/**
 * exec_cmd - execute command
 * @child: new process
 * @array: command
 * @status: execution status
*/
void exec_cmd(pid_t child, char **array, int *status, char **path, char **buf)
{
if (child == -1)
{
perror("Creation Failure");
free_resources(array, buf, path);
exit(EXIT_FAILURE);
}
if (child == 0)
{
if (execve(*path, array, NULL) == -1)
{
perror("Execution Failure");
exit(EXIT_FAILURE);
}
}
else
{
wait(status);
if (WIFEXITED(*status))
{
free_resources(array, buf, path);
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
int status = 0;
(void)argc, (void)argv;
while (1)
{
if (isatty(STDIN_FILENO))
{
write(STDOUT_FILENO, "$ ", 2);
}
if (buf)
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
write(STDOUT_FILENO, "\n", 1);
}
free_resources(NULL, &buf, NULL);
exit(EXIT_SUCCESS);
}
buf[nread - 1] = '\0';
tokenize(&array, buf);
if (!array)
{
continue;
}
path = get_file_path(array[0]);
if (!path)
{
printf("Command not found: %s\n", array[0]);
free_resources(array, &buf, NULL);
continue;
}
child = fork();
exec_cmd(child, array, &status, &path, &buf);
}
free_resources(array, &buf, NULL);
return (0);
}
