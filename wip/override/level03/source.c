#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clear_stdin()
{
    char c = 0;
    c = getchar();

    while (c != '\n' /* 0xa */)
    {
        if (c == -1 /* 0xff */)
            break;
    }
}

unsigned get_unum()
{
    unsigned u = 0;

    fflush(stdout);
    scanf("%u", &u);

    clear_stdin();

    return (u);
}

void prog_timeout()
{
  syscall(SYS_exit, 1);
}

void decrypt(int x)
{
    char buffer[] = "Q}|u`sfg~sf{}|a3";
    
    size_t len = strlen(buffer);
    for (int index = 0; index < len; ++index)
        buffer[index] ^= x;
    
    if (strcmp(buffer, "Congratulations!") == 0)
        system("/bin/sh");
    else
        puts("\nInvalid Password");
}

void test(unsigned passwd, unsigned key)
{
    int x = key - passwd;

    switch(x)
    {
        case 1 /* 0x1 */:
        case 2 /* 0x2 */:
        case 3 /* 0x3 */:
        case 4 /* 0x4 */:
        case 5 /* 0x5 */:
        case 6 /* 0x6 */:
        case 7 /* 0x7 */:
        case 8 /* 0x8 */:
        case 9 /* 0x9 */:
        case 16 /* 0x10 */:
        case 17 /* 0x11 */:
        case 18 /* 0x12 */:
        case 19 /* 0x13 */:
        case 20 /* 0x14 */:
        case 21 /* 0x15 */:
            decrypt(x);
            break;

        default:
            decrypt(rand());
    }
}

int main()
{
    srand(time(0));

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");

    printf("Password:");
    
    unsigned passwd;
    scanf("%d", &passwd);

    test(passwd, 322424845 /* 0x1337d00d */);

    return (0);
}