#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXNODE 500
#define MAXLINENUM 100
#define EXWORDLEN 3
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void nodetovector(struct tnode *v[], struct tnode *p, int *index);
int nodecmp(const void *, const void *);
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* word frequency count */
int main()
{
    struct tnode *root, *v[MAXNODE];
    char word[MAXWORD];
    char *exwords[] = {
        "the",
        "and",
        "or"
    };
    int n, len;

    root = NULL;
    while (getword(word, MAXWORD) != '\0') {
        if (isalpha(word[0])) {
            for(n = 0; n < EXWORDLEN; ++n)
                if (strcmp(word, exwords[n]) == 0)
                    break;
            if (n == EXWORDLEN) root = addtree(root, word);
        }
    }
    len = 0;
    nodetovector(v, root, &len);
    qsort(v, len, sizeof(struct tnode *), nodecmp);
    for (n = 0; n < len; ++n)
        printf("%4d: %s\n", v[n]->count, v[n]->word);
    return 0;
}


struct tnode *talloc(void);
char *strdupX(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond, i;

    if (p == NULL) {
        p = talloc();
        p->word = strdupX(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

void nodetovector(struct tnode *tnodes[], struct tnode *p, int *index)
{
    if (p != NULL && (*index) < MAXNODE) {
        tnodes[(*index)++] = p;
        nodetovector(tnodes, p->left, index);
        nodetovector(tnodes, p->right, index);
    }
}

int nodecmp(const void *n1, const void *n2)
{
    //if ( (*(struct tnode**)n1)->count <  (*(struct tnode**)n2)->count ) return -1;
    if ( (*(struct tnode**)n1)->count == (*(struct tnode**)n2)->count ) return 0;
    else if ( (*(struct tnode**)n1)->count >  (*(struct tnode**)n2)->count ) return 1;
    else return -1;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdupX: make a duplicate of s */
char *strdupX(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);  /* +1 for '\0' */
    if (p != NULL)
        strcpy(p, s);
    return p;
}
/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, c2, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    while ((c = getch()) != EOF && !isspace(c))
        *w++ = c;
    *w = '\0';
    return word[0];
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

void ungets(char s[])
{
    int i = 0;
    char c;
    while((c = s[i++]) != '\0')
        ungetch(c);
}