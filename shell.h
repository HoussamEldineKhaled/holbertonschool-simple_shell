#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

void tokenize(char *token, char **array, int i);
void exec_cmd(pid_t child, char **array, int status);
char *get_file_path(char *file_name);
char *get_file_loc(char *path, char *file_name);
int startsWithForwardSlash(const char *str);

#endif
