#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* removed from c11 standard */
extern char *gets(char *s);

void p()
{
    void *return_address;
    char buffer[76 /* 0x4c */];

    fflush(stdout);
    gets(buffer);

    return_address = __builtin_return_address(0);
    if ((((unsigned long) return_address) & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", return_address);
        _exit(1);
    }

    puts(buffer);
    strdup(buffer);
}

int main(int argc, char const *argv[])
{
    p();
    return (0);
}
