#define NULL    0
#define EOF    (-1)
#define BUFSIZ    1024
#define OPEN_MAX 20

typedef struct _flag {
    int read;
    int write;
    int unbuf;
    int eof;
    int err;
} FLAGS;

typedef struct _iobuf {
    int cnt;
    char *ptr;
    char *base;
    FLAGS flags;
    //int flag;
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

//#define feof(p)     (((p)->flag & _EOF) != 0)
#define feof(p)     ((p)->flags->eof == 1)
//#define ferrror(p)  (((p)->flag & _ERR) != 0)
#define ferrror(p)  ((p)->flags->err == 1)
#define fileno(p)   ((p)->fd)

#define getc(p)    ((--(p)->cnt >= 0) ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)   ((--(p)->cnt >= 0) ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar()   getc(stdin)
#define putchar()   putc((x), stdout)

//////////////////////////////////////

#include <fcntl.h>
//#include "syscalls.h"
#include <unistd.h>
#define PERMS 0666

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        //if ((fp->flag & (_READ | _WRITE)) == 0)
        if (fp->flags.read != 0 &&  fp->flags.write != 0)
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
    //fp->flag = (*mode == 'r') ? _READ : _WRITE;
    if (*mode == 'r')
        fp->flags.read = 1;
    else
        fp->flags.write = 1;
    return fp;

}


//////////////////////////////////////

//#include "syscalls.h"
#include <unistd.h>
#include <stdlib.h>

int _fillbuf(FILE *fp)
{
    int bufsize;

    //if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    if (fp->flags.eof == 1 || fp->flags.err == 1 || fp->flags.read != 1)
        return EOF;
    //bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
    bufsize = fp->flags.unbuf ? 1 : BUFSIZ;
    if (fp->base == NULL)   /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;     /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1)
            //fp->flag |= _EOF;
            fp->flags.eof = 1;
        else
            //fp->flag |= _ERR;
            fp->flags.err = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

FILE _iob[OPEN_MAX] = {
    //{ 0, (char *) 0, (char *) 0, _READ, 0},
    { 0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0},
    //{ 0, (char *) 0, (char *) 0, _WRITE, 1},
    { 0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1},
    //{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2}
    { 0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2}
};

int main()
{
    return 0;
}