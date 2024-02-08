#include <stdio.h>
#include <stdbool.h>
#include "life.h"

void test_isAlive_1(void);

int main(int argc, char *argv[])
{
    test_isAlive_1();
    // test_isAlive_2();
    // test_isAlive_3();
    // test_shouldDie_1();
    // test_shouldDie_2();
    // test_shouldDie_3();
    // ...
}

void test_isAlive_1(void)
{
    int t_arr[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    bool alive = isAlive(t_arr, 0, 10);
    if (alive)
    {
        printf("Passed test_isAlive_1.\n");
    }
    else
    {
        printf("Failed test_isAlive_1.\n");
    }
}
