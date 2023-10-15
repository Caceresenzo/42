#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void p(char *output, const char *prompt)
{
    char buffer[4104];

    puts(prompt);
    read(stdin, buffer, 4096 /* 0x1000 */);

    *strchr(buffer, '\n' /* 0xa */) = '\0';

    strncpy(output, buffer, 20 /* 0x14 */);
}

void pp(char *buffer)
{
    char first[20 /* 0x14 */];
    char second[20 /* 0x14 */];

    p(first, " - ");
    p(second, " - ");

    strcpy(buffer, first);
    buffer[strlen(buffer)] = " "[0] /* ?? */;

    strcat(buffer, second);
}

int main(int argc, char const *argv[])
{
    char buffer[54];

    pp(buffer);
    puts(buffer);

    return (0);
}