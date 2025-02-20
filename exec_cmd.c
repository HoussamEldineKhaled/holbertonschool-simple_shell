#include "shell.h"
/**
 * exec_cmd - execute the command
 * @input: input command
*/
void exec_cmd(char *input)
{
char *args[2];
pit_t pid;
args[0] = strtok(input, "\n");
args[1] = NULL;
pid = fork();
if (pid == 0)
{
if (execve(args[0], args, environ) < 0)
{
perror("Error");
}
exit(EXIT_FAILURE);
}
else
{
wait(NULL);
}
}
