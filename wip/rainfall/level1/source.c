#include <stdio.h>
#include <stdlib.h>

// removed from c11 standard
char *gets(char *s);

void run()
{
    fwrite("Good... Wait what?\n", 1, 19, stdout);

    system("/bin/sh");
}

int main(int argc, char const *argv[])
{
    // 0x50 - 0x16
    char buffer[64];

    gets(buffer);
    return (0);
}
