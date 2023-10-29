#include <stdio.h>
#include <stdlib.h>

unsigned m;

void p(char *buffer)
{
    printf(buffer);
}

void n()
{
    char buffer[520 /* 0x208 */];

    fgets(buffer, 512 /* 0x200 */, stdin);
    p(buffer);

    if (m == 0x1025544)
        system("/bin/cat /home/user/level5/.pass");
}

void main()
{
    n();
}
