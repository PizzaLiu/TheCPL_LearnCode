#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct nlist {      /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text */
};

#define HASHSIZE 101
#define MAXWORD 31
static struct nlist *hashtable[HASHSIZE];   /* pointer table */

int getch(void);
void ungetch(int);

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtable[hash(s)]; np != NULL; np = np->next)
        if (strcmp(np->name, s) == 0)
            return np;     /* found */
    return NULL;                    /* not found */
}

/* install: put (name, defn) in hashtable */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtable[hashval];
        hashtable[hashval] = np;
    } else  /* already there */
        free((void *) np->defn);
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

/* undef: remove (name, defn) in hashtable */
void undef(char *name, char *defn)
{
    struct nlist *np, *prenp;
    unsigned hashval;

    if ((np = lookup(name)) == NULL)    /* not found */
        return;
    hashval = hash(name);
    prenp = NULL;
    for (;np != NULL; np = np->next) {
        if (strcmp(name, np->name) == 0 && strcmp(defn, np->defn) == 0) {
            if (prenp != NULL)
                if (np->next != NULL)
                    prenp->next = np->next;
                else
                    prenp->next = NULL;
            else
                hashtable[hashval] = NULL;
            free(np);
            break;
        }
        prenp = np;
    }
}

int main()
{
    char c, s[MAXWORD], name[MAXWORD], defn[MAXWORD];
    int i;

    while ((c = getch()) != EOF) {
        // found '#'
        if (c == '#') {
            // find 'define'
            i = 0;
            while ((c = getch()) != EOF && !isspace(c) && i < MAXWORD) {
                s[i++] = c;
            }
            s[i] = '\0';

            // find name
            if (strcmp(s, "define") == 0) {
                i = 0;
                while ((c = getch()) != EOF && !isspace(c) && i < MAXWORD) {
                    name[i++] = c;
                }
                name[i] = '\0';
            }

            // find defn
            if (i > 0) {
                i = 0;
                while ((c = getch()) != EOF && !isspace(c) && i < MAXWORD) {
                    defn[i++] = c;
                }
                defn[i] = '\0';
            }
            printf("%s: %s\n", name, defn);
            install(name, defn);
        }
    }
    return 0;
}

//////////////////////////////////////

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (c == EOF)
        printf("ungetch: can't ungetch EOF\n");
    else if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
