#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

char c[80 /* 0x50 */];

void m()
{
    time_t now = time(NULL);

    printf("%s - %d\n", c, (int)now);
}

int main(int argc, char *const argv[])
{
    void **a = malloc(8);
    a[0] = (void*)1;
    a[1] = malloc(8);
    
    void **b = malloc(8);
    b[0] = (void*)2;
    b[1] = malloc(8);

    strcpy(a[1], argv[1]);
    strcpy(b[1], argv[2]);

    FILE *file = fopen("/home/user/level8/.pass", "r");
    fgets(c, 68 /* 0x44 */, file);

    puts("~~");

    return (0);
}
