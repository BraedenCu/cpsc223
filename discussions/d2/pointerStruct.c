#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

int main() {
    char a[] = "XNA";
    char *b = a;
    char **c = &b;

    printf("%s\n", b);
}