/* Minimal shell implementation in C.
 * Needs libreadline-dev to compile.
 * 
 * Compile with:
 * gcc -o minishell minishell.c -lreadline
 *
 * Albert Veli
 * Pungenday, the 41st day of The Aftermath in the YOLD 3190
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_ARGS 64

void parse_input(char *input, char **args)
{
	int i = 0;
	args[i] = strtok(input, " \t\n");
	while (args[i] != NULL) {
		i++;
		args[i] = strtok(NULL, " \t\n");
	}
}

int main(void)
{
	char *args[MAX_ARGS];
	char *input;
	pid_t pid;
	int status;

	while (1) {

		/* prompt */
		input = readline("$ ");
		if (!input) {
			break;
		}

		if (*input) {
			add_history(input);
		}

		if (strlen(input) == 0) {
			free(input);
			continue;
		}

		parse_input(input, args);

		if (strcmp(args[0], "exit") == 0) {
			/* exit with exit */
			free(input);
			break;
		}

		pid = fork();
		if (pid < 0) {
			perror("fork");
			free(input);
			continue;
		}

		if (pid == 0) {
			/* child */
			if (execvp(args[0], args) == -1) {
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		} else {
			/* parent */
			if (waitpid(pid, &status, 0) == -1) {
				perror("waitpid");
			}
		}

		free(input);
	}

	printf("Bye!\n");

	return 0;
}

