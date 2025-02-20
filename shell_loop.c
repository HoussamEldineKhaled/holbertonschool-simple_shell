#include "shell.h"

/**
 * shell_loop - execute commands in shell
*/

void shell_loop()
{
char *input = NULL;
size_t len = 0;
size_t end;
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
if (input[nread - 1] == '\n')
{
input[nread - 1] = '\0';
}
end = strlen(input);
while (end > 0 && input[end - 1] == ' ')
{
input[--end] = '\0';
}
if (strcmp(input, "\n") == 0)
{
continue;
}
exec_cmd(input);
}
free(input);
}
