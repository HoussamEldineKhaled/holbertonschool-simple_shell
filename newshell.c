#include "shell.h"
#define MAX_INPUT_SIZE 1024


int main(int argc, char **argv, char **env)
{
  char input[MAX_INPUT_SIZE];
  char *args[MAX_INPUT_SIZE];
  int i;
  pid_t child;
  int status;

  (void)argc;
  (void)argv;

  while(1)
    {
      printf("$ ");
      if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
	{
	  printf("\n");
	  break;
	}
      input[strcspn(input, "\n")] = '\0';
      args[0] = strtok(input, " ");
      
    }
}
