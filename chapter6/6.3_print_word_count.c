#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define MAXLINENUM 100
#define EXWORDLEN 3
struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int, int *);

/* word frequency count */
int main()
{
    struct tnode *root;
    char word[MAXWORD];
    char *exwords[] = {
        "the",
        "and",
        "or"
    };
    int n, lnum;

    root = NULL;
    while (getword(word, MAXWORD, &lnum) != '\0') {
        if (isalpha(word[0])) {
            for(n = 0; n < EXWORDLEN; ++n)
                if (strcmp(word, exwords[n]) == 0)
                    break;
            if (n == EXWORDLEN) root = addtree(root, word, lnum);
        }
    }
    treeprint(root);
    return 0;
}

struct tnode {
    char *word;
    int count;
    int line_nums[MAXLINENUM];
    struct tnode *left;
    struct tnode *right;
};

void addLineNum(int line_nums[], int lnum)
{
    int i;

    for (i = 0; i < MAXLINENUM; ++i)
        if (line_nums[i] == 0) {
            line_nums[i] = lnum;
            break;
        }
}

struct tnode *talloc(void);
char *strdupX(char *);

struct tnode *addtree(struct tnode *p, char *w, int lnum)
{
    int cond, i;

    if (p == NULL) {
        p = talloc();
        p->word = strdupX(w);
        p->count = 1;
        p->left = p->right = NULL;
        for (i = 0; i < MAXLINENUM; ++i)
            p->line_nums[i] = 0;
        addLineNum(p->line_nums, lnum);
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
        addLineNum(p->line_nums, lnum);
    } else if (cond < 0)
        p->left = addtree(p->left, w, lnum);
    else
        p->right = addtree(p->right, w, lnum);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;

    if (p != NULL) {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        for (i = 0; i < MAXLINENUM; ++i) {
            if (p->line_nums[i] == 0)
                break;
            printf("\t%4d.%d\n", i+1, p->line_nums[i]);
        }
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
int getword(char *word, int lim, int *lnum)
{
    int c, c2, getch(void);
    void ungetch(int);
    char *w = word;
    static int line_num = 1;

    while (isspace(c = getch())) {
        if (c == '\n')
            line_num++;
    }
    *lnum = line_num;
    if (c != EOF)
        *w++ = c;
    while ((c = getch()) != EOF && !isspace(c)) {
        *w++ = c;
    }
    if (c == '\n')
        line_num++;
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