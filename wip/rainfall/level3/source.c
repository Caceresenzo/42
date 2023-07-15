#include <stdio.h>

unsigned m;

void v()
{
    char buffer[520 /* 0x208 */];

    fgets(buffer, 512 /* 0x200 */, stdin);
    printf(buffer);
    
    if (m == 64 /* 0x40 */)
    {
        fwrite("Wait what?!\n", 1, 12, stdout);
        system("/bin/sh");
    }
}

int main()
{
    v();
}
