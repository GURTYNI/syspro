#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char savedText[10][100] = {0};
    char input[100], ch;
    int row = 0, col = 0;
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1)
        return 1;

    while (read(fd, &ch, 1) > 0) {
        if (ch == '\n') {
            row++;
            col = 0;
        } else {
            savedText[row][col++] = ch;
        }
    }

    close(fd);

    int count = row + (col > 0);

    printf("File read success\n");
    printf("Total Line : %d\n", count);
    printf("You can choose 1 ~ %d Line\n", count);
    printf("Pls 'Enter' the line to select : ");

    if (scanf("%99s", input) != 1)
        return 0;

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < count; i++)
            printf("%s\n", savedText[i]);
    } else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);

        for (int i = start; i <= end; i++)
            printf("%s\n", savedText[i - 1]);
    } else {
        char *token = strtok(input, ",");

        while (token != NULL) {
            int n = atoi(token);
            printf("%s\n", savedText[n - 1]);
            token = strtok(NULL, ",");
        }
    }

    return 0;
}
