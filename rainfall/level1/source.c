#include <stdio.h>
#include <stdlib.h>

/* removed from c11 standard */
extern char *gets(char *s);

void run()
{
    fwrite("Good... Wait what?\n", 1, 19, stdout);

    system("/bin/sh");
}

int main(int argc, char const *argv[])
{
    /* 0x50 - 0x10 */
    char buffer[64];

    gets(buffer);
    return (0);
}
