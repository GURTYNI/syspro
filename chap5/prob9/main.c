#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char savedText[10][100] = {0};
    char ch;
    int row = 0, col = 0;
    int fd = open(argv[1], O_RDONLY);

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

    for (int i = count - 1; i >= 0; i--)
        printf("%s\n", savedText[i]);

    return 0;
}
