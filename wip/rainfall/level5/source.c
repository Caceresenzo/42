#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void o()
{
    system("/bin/sh");
    _exit(1);
}

void n()
{
    char buffer[520 /* 0x208 */];

    fgets(buffer, 512 /* 0x200 */, stdin);
    printf(buffer);

    exit(1);
}

void main()
{
    n();
}
