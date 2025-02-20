#include "shell.h"


/**
 * find_in_path - handle PATH
 * @cmd: command input
*/


char *find_in_path(char *cmd)
{
char *path = getenv("PATH");
char *token, full_path[1024];
token = strtok(path, ":");
while (token)
{
sprintf(full_path, "%s/%s", token, cmd);
if (access(full_path, X_OK) == 0)
{
return strdup(full_path);
}
token = strok(NULL, ":");
}
return NULL;
}
