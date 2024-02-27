#include <stdio.h>
#include <stdlib.h>

struct point {
    int x;
    int y;
};

int main() {
    char a[] = "XNA";
    char *b = a;
    char **c = &b;
    struct point *d = malloc(sizeof(struct point));
    d->x = 1;
    d->y = 2;
    int *e = malloc(2*sizeof(int));
    e[0] = 0;
    e[1] = 1;
    int *f[2];
    f[0] = e+1;
    f[1] = malloc(sizeof(int));
    *f[1] = -1;


    printf("%s\n", b);
}