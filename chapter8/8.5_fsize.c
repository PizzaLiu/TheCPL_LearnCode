#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/dir.h>
#include <time.h>

#define NAME_MAX  255    /* logest filename component; */
/*
struct stat
{
    dev_t   st_dev;
    ino_t   st_ino;
    short   st_mode;
    short   st_nlink;
    short   st_uid;
    short   st_gid
    dev_t   st_rdev;
    off_t   st_size;
    time_t  st_atime;
    time_t  st_mtime;
    time_t  st_ctime;
}
*/

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[NAME_MAX+1];
    struct dirent *dp;

    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL) {
            fprintf(stderr, "dirwalk: can't open %s\n", dir);
            return;
    }

    while ((dp = readdir(dfd)) != NULL) {
            if (strcmp(dp->d_name, ".") == 0
                            || strcmp(dp->d_name, "..") == 0)
                    continue;
            if (strlen(dir)+strlen(dp->d_name)+2 > sizeof(name))
                    fprintf(stderr, "dirwalk: name %s/%s too long\n",
                                    dir, dp->d_name);
            else {
                    sprintf(name, "%s/%s", dir, dp->d_name);
                    (*fcn)(name);
            }
    }
    closedir(dfd);
}

/* fsize: print the name of file "name" */
void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1) {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);

    printf("%d %d %s %8lld %s\n", stbuf.st_mode, stbuf.st_uid, ctime(&stbuf.st_ctime), stbuf.st_size, name);

}

/* print file name */
int main(int argc, char **argv)
{
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}