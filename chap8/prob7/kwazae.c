#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
		
extern char **environ;
	
int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s [-e [name] | -u | -g | -i | -p]\n", argv[0]);
		return 1;
	}	
	if (strcmp(argv[1], "-e") == 0) {
		if (argc >= 3) {
			char *value = getenv(argv[2]);
	
			if (value != NULL)printf("%s=%s\n", argv[2], value);
			else printf("환경변수가 없습니다.\n");
		}
		else {
			for (int i = 0; environ[i] != NULL; i++)
			printf("%s\n", environ[i]);
		}
	}
	else if (strcmp(argv[1], "-u") == 0) {
		printf("My Reatistic User ID: %d(%s)\n", getuid(),getpwuid(getuid())->pw_name);
		printf("My Valid User ID: %d(%s)\n", geteuid(),getpwuid(geteuid())->pw_name);
	}
	else if (strcmp(argv[1], "-g") == 0) {
		printf("My Realistic Group ID: %d(%s)\n", getgid(),getpwuid(getuid())->pw_name);
		printf("My Valid Group ID: %d(%s)\n", getegid(),getpwuid(getuid())->pw_name);
	}
	else if (strcmp(argv[1], "-i") == 0) {
		printf("my process number: [%d]\n", getpid());
	}
	else if (strcmp(argv[1], "-p") == 0) {
		printf("my parent's process number: [%d]\n", getppid());
	}
	else {
		printf("잘못된 옵션입니다.\n");
	}

	return 0;
}
