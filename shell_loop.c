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
if (nread < 0)
{
printf("\n");
break;
}
if (strcmp(input, "\n") == 0)
{
continue;
}
exec_cmd(input);
}
free(input);
}
