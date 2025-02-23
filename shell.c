#include "shell.h"
#define MAX_INPUT_SIZE 1024


/**
 * get_path_from_env - get env path
 * @env: environment variable
 * Return: NULL or env
*/


char *get_path_from_env(char **env)
{
int i = 0;
while (env[i] != NULL)
{
if (strncmp(env[i], "PATH=", 5) == 0)
{
return (env[i] + 5);
}
i++;
}
return (NULL);
}


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
if (args[0][0] == '/' || args[0][0] == '.')
{
if (stat(args[0], &st) == 0 && (st.st_mode & S_IXUSR))
{
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
fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
free(input);
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}
}
else
{
fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
}
}
else
{
path = get_path_from_env(env);
if (path == NULL)
{
fprintf(stderr, "PATH not found in environment\n");
free(input);
input = NULL;
continue;
}
path_copy = strdup(path);
dir = strtok(path_copy, ":");
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
full_path = NULL;
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
if (execve(full_path, args, env) == -1)
{
perror(args[0]);
free(full_path);
free(input);
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}
free(full_path);
}
free(input);
input = NULL;
}
return (0);
}
