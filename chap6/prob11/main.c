#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat buf;

    int opt_i = 0;
    int opt_p = 0;
    int opt_Q = 0;

    char *path = ".";
    char fullpath[PATH_MAX];

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0)
            opt_i = 1;
        else if (strcmp(argv[i], "-p") == 0)
            opt_p = 1;
        else if (strcmp(argv[i], "-Q") == 0)
            opt_Q = 1;
        else
            path = argv[i];
    }

    dp = opendir(path);

    if (dp == NULL) {
        perror("opendir()");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {

        snprintf(fullpath, sizeof(fullpath),
                 "%s/%s", path, entry->d_name);

        if (lstat(fullpath, &buf) == -1) {
            perror("lstat()");
            continue;
        }

        if (opt_i)
            printf("%lu ", (unsigned long)buf.st_ino);

        if (opt_Q)
            printf("\"%s\"", entry->d_name);
        else
            printf("%s", entry->d_name);

        if (opt_p && S_ISDIR(buf.st_mode))
            printf("/");

        printf("\n");
    }

    closedir(dp);

    return 0;
}

