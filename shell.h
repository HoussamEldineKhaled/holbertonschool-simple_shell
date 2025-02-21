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

#endif
