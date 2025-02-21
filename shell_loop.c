#include "shell.h"


/**
 * shell_loop - execute commands in shell
*/

void shell_loop()
{
char *input = NULL;
size_t len = 0;
ssize_t nread;
while (1)
{
if (isatty(STDIN_FILENO))
{
printf("$ ");
}
nread = getline(&input, &len, stdin);
if (nread == -1)
{
if (isatty(STDIN_FILENO))
{
printf("\n");
}
break;
}
if (input[nread - 1] == '\n')
{
input[nread - 1] = '\0';
}
if (strlen(input) > 0)
{
exec_cmd(input);
}
}
free(input);
}
