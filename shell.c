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
char input[MAX_INPUT_SIZE];
char *args[MAX_INPUT_SIZE];
int i;
pid_t child;
int status;
(void)argc;
(void)argv;
while(1)
{
printf("$ ");
if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
{
printf("\n");
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
exit(EXIT_FAILURE);
}
else if (child == 0)
{
if (execve(args[0], args, env) == -1)
{
perror(args[0]);
exit(EXIT_FAILURE);
}
}
else
{
wait(&status);
}
}
return (0);
}
