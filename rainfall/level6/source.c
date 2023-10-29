#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void n()
{
    system("/bin/cat /home/user/level7/.pass");
}

void m()
{
    puts("Nope");
}

typedef void (*func)();

void main(int argc, char *const argv[])
{
    void *a = malloc(64 /* 0x40 */);
    func *b = malloc(4 /* 0x4 */);

    *b = (void*)m;
    strcpy(a, argv[1]);

    (*b)();
}
