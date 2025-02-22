#include "shell.h"
#define MAX_INPUT_SIZE 1024


/**
 * main - shell program
 * @argc: arg size
 * @argv: value
 * @env: environemnt
 * Return: 0 always
*/
int main(int argc, char **argv, char **env)
{
char *input = NULL, *dir, *full_path, *path;
char *path_copy;
char *args[MAX_INPUT_SIZE];
int i , status, command_found;
size_t size = 0;
pid_t child;
struct stat st;
(void)argc;
(void)argv;
while(1)
{
if (isatty(STDIN_FILENO))
{
printf("$ ");
}
if (getline(&input, &size, stdin) == -1)
{
if (isatty(STDIN_FILENO))
{
printf("\n");
}
free(input);
break;
}
input[strcspn(input, "\n")] = '\0';
args[0] = strtok(input, " ");
i = 0;
while (args[i] != NULL)
{
i++;
args[i] = strtok(NULL, " ");
}
if (args[0] == NULL)
{
free(input);
input = NULL;
continue;
}
path = getenv("PATH");
path_copy = strdup(path);
full_path = NULL;
command_found = 0;
while (dir != NULL)
{
full_path = malloc(strlen(dir) + strlen(args[0]) + 2);
if (full_path == NULL)
{
perror("malloc");
free(path_copy);
free(input);
exit(EXIT_FAILURE);
}
sprintf(full_path, "%s/%s", dir, args[0]);
if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
{
command_found = 1;
break;
}
free(full_path);
dir = strtok(NULL, ":");
}
free(path_copy);
if (!command_found)
{
fprintf(stderr, "%s: command not found\n", args[0]);
free(input);
input = NULL;
continue;
}
child = fork();
if (child == -1)
{
perror("fork");
free(input);
exit(EXIT_FAILURE);
}
else if (child == 0)
{
if (execve(args[0], args, env) == -1)
{
perror(args[0]);
free(input);
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}
free(input);
input = NULL;
}
return (0);
}
