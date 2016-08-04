#define NULL    0
#define EOF    (-1)
#define BUFSIZ    1024
#define OPEN_MAX 20

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE;

extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

enum _flags {
    _READ   = 01,
    _WRITE  = 02,
    _UNBUF  = 04,
    _EOF    = 010,
    _ERR    = 020
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p)     (((p)->flag & _EOF) != 0)
#define ferrror(p)  (((p)->flag & _ERR) != 0)
#define fileno(p)   ((p)->fd)

#define getc(p)    ((--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)   ((--(p)->cnt >= 0) ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar()   putc((x), stdout)

//////////////////////////////////////

#include <fcntl.h>
//#include "syscalls.h"
#include <unistd.h>
#include <stdlib.h>
#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;
    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd =creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;

}

int _flushbuf(int c, FILE *fp)
{
    int bufsize;

    if (fp == NULL)
        return EOF;

    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    if (fp->base == NULL) {
        if ((fp->base = malloc(bufsize)) == NULL)
            return EOF;
    } else {
        if (write(fp->fd, fp->base, bufsize) != bufsize) {
            fp->flag |= _ERR;
            return EOF;
        }
    }
    fp->ptr = fp->base;
    fp->cnt = bufsize - 1;
    return (*fp->ptr++ = c);
}

int fflush(FILE *fp)
{
    int bufsize, write_size;

    if (fp == NULL)
        return EOF;
    if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
        return EOF;
    if (fp->base == NULL)
        return 0;

    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;

    //write_size = fp->ptr - fp->base;
    write_size = bufsize - fp->cnt;
    if (write(fp->fd, fp->base, write_size) != write_size) {
        fp->flag |= _ERR;
        return EOF;
    }

    fp->ptr = fp->base;
    fp->cnt = bufsize;
    return 0;
}

int fclose(FILE *fp)
{
    if (fp->flag & _WRITE) {
        if (fflush(fp) != 0)
            return EOF;
    }

    fp->flag = 0;
    free(fp->base);
    close(fp->fd);
    return 0;
}

int fseek(FILE *fp, long offset, int origin)
{
    int status, mode = 1;
    char c;
    void ungetch(int, FILE *);


    if (fp->base == NULL)
        return 1;
    switch (origin) {
        case SEEK_SET:
            mode = 0;
            break;
        case SEEK_CUR:
            mode = 1;
            break;
        case SEEK_END:
            mode = 2;
            break;
    }

    status = lseek(fp->fd, offset, mode);
    if (status == -1)
        return 1;
    if (fp->flag & _READ) {
        c = _fillbuf(fp);
        ungetch(c, fp);
    } else {
        fflush(fp);
    }

    return 0;
}

//////////////////////////////////////

//#include "syscalls.h"
#include <unistd.h>
#include <stdlib.h>

int _fillbuf(FILE *fp)
{
    int bufsize;

    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)   /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;     /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = {
    { 0, (char *) 0, (char *) 0, _READ, 0},
    { 0, (char *) 0, (char *) 0, _WRITE, 1},
    { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
};

//////////////////////////////////////
void ungetch(int c, FILE *fp)
{
    if (fp->cnt < 1)
        return;
    fp->cnt--;
    *fp->ptr++ = c;
}


int main()
{
    return 0;
}