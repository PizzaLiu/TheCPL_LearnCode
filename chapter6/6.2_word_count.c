#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

struct key {
    char *word;
    int count;
};

struct key keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "do", 0,
    "double", 0,
    "else", 0,
    "enum", 0,
    "extern", 0,
    "float", 0,
    "for", 0,
    "goto", 0,
    "if", 0,
    "int", 0,
    "long", 0,
    "register", 0,
    "return", 0,
    "short", 0,
    "signed", 0,
    "sizeof", 0,
    "static", 0,
    "struct", 0,
    "switch", 0,
    "typedef", 0,
    "union", 0,
    "unsigned", 0,
    "void", 0,
    "volatite", 0,
    "while", 0
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(struct key))
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main()
{
    struct tnode *root;
    char word[MAXWORD];
    int n;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0])) {
            for (n = 0; n < NKEYS; n++)
                if (strcmp(word, keytab[n].word) == 0)
                    break;
            if (n == NKEYS) root = addtree(root, word);
        }
    treeprint(root);
    return 0;
}

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void);
char *strdupX(char *);

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

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

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
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
    if (!isalpha(c)) {
        // comments
        if (c == '/') {
            // one line comments
            if((c = getch()) == '/')
                while ((c = getch()) != '\n')
                    ;
            // multiline/oneline comments
            else if(c == '*') {
                while ((c = getch()) != '*' && (c2 = getch()) != '/')
                    ungetch(c2);
            } else
                ungetch(c);
        // string
        } else if (c == '\"')
            while ((c = getch()) != '"')
                    ;
        // char
        else if (c == '\'')
            while ((c = getch()) != '\'')
                    ;
        // preprocessor
        else if(c == '#')
                while ((c = getch()) != '\n')
                    ;
        // underscore
        else
            while ((c = getch()) != EOF && !isspace(c))
                    ;
        if (c != '\"' && c != '\n' && c != '/' && c != EOF)
            ungetch(c);
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
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
