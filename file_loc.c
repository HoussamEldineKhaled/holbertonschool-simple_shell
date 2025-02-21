#include "shell.h"



/**
 * get_file_loc - location of file
 * @path: file path
 * @file_name: file name
 * Return: NULL or location
*/


char *get_file_loc(char *path, char *file_name)
{
char *path_copy, *token;
struct stat file_path;
char *path_buffer = NULL;
path_copy = strdup(path);
token = strtok(path_copy, ":");
while (token)
{
if (path_buffer)
{
free(path_buffer);
path_buffer = NULL;
}
path_buffer = malloc(strlen(token) + strlen(file_name) + 2);
if (path_buffer)
{
perror("Error: failed malloc");
exit(EXIT_FAILURE);
}
strcpy(path_buffer, token);
strcat(path_buffer, "/");
strcat(path_buffer, file_name);
strcat(path_buffer, "\0");
if (stat(path_buffer, &file_path) == 0 && access(path_buffer, X_OK) == 0)
{
free(path_copy);
return (path_buffer);
}
token = strtok(NULL, ":");
}
free(path_copy);
if (path_buffer)
{
free(path_buffer);
}
return (NULL);
}



/**
 * get_file_path - get the file path
 * @file_name: name of file
 * Return: NULL or the full path
*/



char *get_file_path(char *file_name)
{
char *full_path;
char *path = getenv("PATH");
if (!path)
{
perror("Path not found");
return (NULL);
}
full_path = get_file_loc(path, file_name);
if (full_path == NULL)
{
perror("Absolute path not found");
return (NULL);
}
return (full_path);
}
