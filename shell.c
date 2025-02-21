#include "shell.h"

/**
 * main - execute the shell loop
 * argc: argument count
 * argv: argument value
 * Return: 0
*/
int main(int argc, char *argv[])
{
(void)argc, (void)argv;
write(STDOUT_FILENO, "$ ", 2);
return (0);
}
