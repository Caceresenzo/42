#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char passwd[112 /* 0x110-0xa0 */] = { 0 };
    char flag[48 /* 0xa0-0x70 */] = { 0 };
    char login[100 /* 0x70-0xc */] = { 0 };

    int read = 0;
    FILE *stream = NULL;
    
    stream = fopen("/home/users/level03/.pass", "r");
    if (stream == NULL)
    {
        fwrite("ERROR: failed to open password file\n", 1, 36 /* 0x24 */, stderr);
        exit(1);
    }

    read = fread(flag, 1, 41 /* 0x29 */, stream);
    flag[strcspn(flag, "\n")] = '\0';

    if (read != 41 /* 0x29 */) {
        fwrite("ERROR: failed to read password file\n", 1, 36 /* 0x24 */, stderr);
        fwrite("ERROR: failed to read password file\n", 1, 36 /* 0x24 */, stderr);
        exit(1);
    }

    fclose(stream);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");

    printf("--[ Username: ");
    fgets(login, 100 /* 0x64 */, stdin);
    login[strcspn(login, "\n")] = 0;

    printf("--[ Password: ");
    fgets(passwd, 100 /* 0x64 */, stdin);
    passwd[strcspn(passwd, "\n")] = 0;
    
    puts("*****************************************");

    if (strncmp(flag, passwd, 41 /* 0x29 */))
    {
        printf("Greetings, %s!\n", login);
        system("/bin/sh");
        return (0);
    }
    
    printf(login);
    puts(" does not have access!");
    exit(1);
}
