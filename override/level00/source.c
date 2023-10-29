#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");

    printf("Password:");

    int value;
    scanf("%d", &value);

    if (value == 5276 /* 0x149c */)
    {
        puts("\nAuthenticated!");
        system("/bin/sh");
        return (0);
    }

    puts("\nInvalid Password!");
    return (1);
}
