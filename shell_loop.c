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
printf("$ ");
nread = getline(&input, &len, stdin);
if (nread < 0)
{
printf("\n");
break;
}
exec_cmd(input);
}
free(input);
}
