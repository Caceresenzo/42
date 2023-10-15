#include <stdio.h>
#include <limits.h>

void print(unsigned y)
{
    printf("y = %u\n", y);
}

int main(int argc, char const *argv[])
{
    int x = -((UINT_MAX / 4) - 10);

    printf("x = %d\n", x);
    print(x * 4);

    return (0);
}
