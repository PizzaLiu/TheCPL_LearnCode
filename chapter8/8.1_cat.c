#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define BUFSIZE 255

int main(int argc, char *argv[])
{
    int fd;
    void filecopy(int, int);

    if (argc == 1)
        filecopy(STDIN, STDOUT);
    else 
        while (--argc > 0)
            if((fd = open(*++argv, O_RDONLY, 0)) == -1) {
                exit(1);
            } else {
                filecopy(fd, STDOUT);
                close(fd);
            }
    exit(0);
}

void filecopy(int in, int out)
{
    char buf[BUFSIZE];
    int n;
    while((n = read(in, buf, BUFSIZE)) > 0)
        write(out, buf, n);
}