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
char *input = NULL;
char *args[MAX_INPUT_SIZE];
int i;
size_t size = 0;
pid_t child;
int status;
(void)argc;
(void)argv;
while(1)
{
printf("$ ");
if (getline(&input, &size, stdin) == -1)
{
printf("\n");
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
