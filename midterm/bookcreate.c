#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "db.dat"
#define max 30

struct book{
	int id;
	char bookname[max];
	char author[max];
	int year;
	int numofborrow;
};
int main(int argc, char *argv[])
{
   int fd;
   struct book record;
   if (argc < 2) {
      fprintf(stderr,"How to use: %s file\n", argv[0]);
      exit(1);
   }
   if ((fd = open(argv[1], O_WRONLY|O_CREAT|O_EXCL, 0640)) == -1) {
      perror(argv[1]);
      exit(2);
   }
   printf("%-9s %-9s %-9s %-9s %-9s %-9s\n","id","bookname","author","year","numofborrow","borrow");
   while (scanf("%d %s %d %d %d", &record.id, record.bookname, &record.author,&record.year, &record.numofborrow) == 5) {
      lseek(fd, (record.id) * sizeof(record), SEEK_SET);
      write(fd, (char *) &record, sizeof(record) );
   }
   close(fd);
   exit(0);
}


