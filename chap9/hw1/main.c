#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 1024
#define MAXARG 100

void execute(char *command)
{
	char *args[MAXARG];
	char *token;
	char *saveptr;
	char *input = NULL;
	char *output = NULL;
	int argc = 0;
	int background = 0;
	int fd, pid;

	token = strtok_r(command, " \t\n", &saveptr);

	while (token != NULL && argc < MAXARG - 1) {
		if (strcmp(token, "<") == 0) {
			token = strtok_r(NULL, " \t\n", &saveptr);
			input = token;
		}
		else if (strcmp(token, ">") == 0) {
			token = strtok_r(NULL, " \t\n", &saveptr);
			output = token;
		}
		else if (strcmp(token, "&") == 0) {
			background = 1;
		}
		else {
			args[argc++] = token;
		}

		token = strtok_r(NULL, " \t\n", &saveptr);
	}

	args[argc] = NULL;

	if (argc == 0)
		return;

	pid = fork();

	if (pid == 0) {
		if (input != NULL) {
			fd = open(input, O_RDONLY);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			dup2(fd, 0);
			close(fd);
		}

		if (output != NULL) {
			fd = open(output, O_CREAT | O_TRUNC | O_WRONLY, 0660);
			if (fd < 0) {
				perror("open");
				exit(1);
			}
			dup2(fd, 1);
			close(fd);
		}
	
		execvp(args[0], args);
		perror("execvp");
		exit(1);
	}
	else if (pid < 0) {
		perror("fork");
	}
	else if (!background) {
		waitpid(pid, NULL, 0);
	}
	else {
		printf("Background PID: %d\n", pid);
	}
}

int main()
{
	char line[MAXLINE];
	char *command;
	char *saveptr;

	while (1) {
		while (waitpid(-1, NULL, WNOHANG) > 0);

		printf("[shell] ");
		fflush(stdout);
	
		if (fgets(line, sizeof(line), stdin) == NULL)
			break;
	
		if (strcmp(line, "exit\n") == 0)
			break;
	
		command = strtok_r(line, ";\n", &saveptr);
	
		while (command != NULL) {
			execute(command);
			command = strtok_r(NULL, ";\n", &saveptr);
		}
	}
	
	return 0;
}
