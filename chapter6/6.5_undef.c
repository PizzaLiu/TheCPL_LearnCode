#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {      /* table entry: */
    struct nlist *next;     /* next entry in chain */
    char *name;             /* defined name */
    char *defn;             /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtable[HASHSIZE];   /* pointer table */

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
    char name[] = "IN", defn[] = "1";
    struct nlist *np;

    printf("Install %s: %s\n", name, defn);
    install(name, defn);
    printf("Lookup: %s\n", name);
    np = lookup(name);
    if (np != NULL)
        printf("\tfound it %s: %s\n", np->name, np->defn);
    printf("Uninstall %s: %s\n", name, defn);
    undef(name, defn);
    printf("Lookup: %s\n", name);
    np = lookup(name);
    if (np == NULL)
        printf("\tnot found, np = NULL");
    return 0;
}