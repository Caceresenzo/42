#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char a_user_name[0x64 /* 100*/];

int verify_user_name()
{
    puts("verifying username....\n");
    return (strncmp(a_user_name, "dat_wil", 7));
}

int verify_user_pass(char *passwd)
{
    return (strncmp(passwd, "admin", 7));
}

int main(int argc, char const *argv[])
{
    int result;
    char passwd[64 /* 0x5c - 0x1c */] = { 0 };

    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");
    fgets(a_user_name, 256 /* 0x100 */, stdin);

    result = verify_user_name();
    if (result != 0)
    {
        puts("nope, incorrect username...\n");
        return (1);
    }

    puts("Enter Password: ");
    fgets(passwd, 100 /* 0x64 */, stdin);

    result = verify_user_pass(passwd);
    if (result == 0)
    {
        puts("nope, incorrect password...\n");
        return (1);
    }
    
    if (result == 0)
        return (0);
    
    puts("nope, incorrect password...\n");
    return (1);
}
