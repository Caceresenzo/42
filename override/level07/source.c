#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>

/* removed from c11 standard */
extern char *gets(char *s);

void clear_stdin()
{
    char c = 0;

    do
    {
        c = getchar();
        printf("`%d`\n", c);
        if (c == '\n' /* 0xa */)
            break;
    } while (c != -1 /* 0xff */);
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

__attribute__((constructor))
void enable_timeout_cons()
{
    signal(SIGALRM /* 0xe */, &prog_timeout);
    alarm(60 /* 0x3c */);
}

unsigned store_number(unsigned *buffer)
{
    unsigned number = 0;
    unsigned index = 0;

    printf(" Number: ");
    number = get_unum();

    printf(" Index: ");
    index = get_unum();

    if ((index % 3) == 0 || (index >> 24 /* 0x18 */) == 183 /* 0xb7 */)
    {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return (1);
    }

    buffer[index] = number;
    return (0);
}

unsigned read_number(unsigned *buffer)
{
    unsigned index = 0;

    printf(" Index: ");
    index = get_unum();

    printf(" Number at data[%u] is %u\n", index, buffer[index]);

    return (0);
}

int main(int argc, char **argv, char **envp)
{
    unsigned error = 0;
    char command[20 /* 0x14 */] = { 0 };
    unsigned storage[100 /* (0x1cc - (0x10 + 0x18 + 0x14)) / 4 */] = { 0 };

    while (*argv)
    {
        memset(*argv, 0, sizeof(*argv));
        *argv++;
    }

    while (*argv)
    {
        memset(*argv, 0, sizeof(*argv));
        *argv++;
    }

    puts(
        "----------------------------------------------------\n"
        "  Welcome to wil's crappy number storage service!   \n"
        "----------------------------------------------------\n"
        " Commands:                                          \n"
        "    store - store a number into the data storage    \n"
        "    read  - read a number from the data storage     \n"
        "    quit  - exit the program                        \n"
        "----------------------------------------------------\n"
        "   wil has reserved some storage :>                 \n"
        "----------------------------------------------------\n"
    );

    while (1)
    {
        printf("Input command: ");

        error = 1;
        fgets(command, 20 /* 0x14 */, stdin);
        command[strlen(command) - 1] = '\0';

        if (strncmp(command, "store", 5) == 0)
            error = store_number(storage);
        else if (strncmp(command, "read", 4) == 0)
            error = read_number(storage);
        else if (strncmp(command, "quit", 4) == 0)
            break ;

        if (error)
            printf(" Failed to do %s command\n", command);
        else
            printf(" Completed %s command successfully\n", command);
        
        memset(command, 0, sizeof(command));
    }
}
