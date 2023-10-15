#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char passwd[66 /* 0x42 */];
    char buffer[66 /* 0x42 */];
    FILE *file;
    
    file = fopen("/home/user/end/.pass", "r");
    memset(passwd, 0, sizeof(passwd));

    if (!file || argc != 2)
        return (-1);
    
    fread(passwd, 1, 66 /* 0x42 */, file);
    passwd[atoi(argv[1])] = '\0';
    
    fread(buffer, 1, 66 /* 0x42 */, file);
    fclose(file);

    if (!strcmp(passwd, argv[1]))
        execl("/bin/sh", "sh", NULL);
    else
        puts(buffer);

    return (0);
}