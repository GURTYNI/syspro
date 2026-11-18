#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 100

int main()
{
	char line[MAXLINE];
	char *args[MAXARG];
	char *token;
	char *saveptr;
	int argc, background, pid;

	while (1) {
		while (waitpid(-1, NULL, WNOHANG) > 0);

		printf("[Shell] ");
		fflush(stdout);

		if (fgets(line, sizeof(line), stdin) == NULL)
			break;

		argc = 0;
		background = 0;

		token = strtok_r(line, " \t\n", &saveptr);

		while (token != NULL && argc < MAXARG - 1) {
			args[argc++] = token;
			token = strtok_r(NULL, " \t\n", &saveptr);
		}

		args[argc] = NULL;

		if (argc == 0)
			continue;

		if (strcmp(args[0], "exit") == 0)
			break;

		if (strcmp(args[argc - 1], "&") == 0) {
			background = 1;
			args[--argc] = NULL;
		}

		if (argc == 0)
			continue;

		pid = fork();

		if (pid == 0) {
			execvp(args[0], args);
			perror("execvp");
			exit(1);
		}
		else if (pid < 0) {
			perror("fork");
		}
		else {
			if (background == 0) {
				waitpid(pid, NULL, 0);
			}
			else {
				printf("Background PID: %d\n", pid);
			}
		}
	}

	return 0;
}
