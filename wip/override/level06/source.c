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

__attribute__((constructor))
void enable_timeout_cons()
{
    signal(SIGALRM /* 0xe */, &prog_timeout);
    alarm(60 /* 0x3c */);
}

int auth(char *login, unsigned serial)
{
    size_t length;

    length = strcspn(login, "\n");
    login[length] = '\0';

    length = strnlen(login, 0x20);
    if (length <= 5)
        return (1);
    
    if (ptrace(PTRACE_TRACEME /* 0x0 */, 0, (void*)1, NULL) == -1)
    {
        puts("\033[32m.--------------------------.");
        puts("\033[31m| !! TAMPERING DETECTED !!  |");
        puts("\033[32m'--------------------------'");
        return (1);
    }

    unsigned hash = ((int) login[3]) ^ 0x1337 + 0x5eeded;
    for (unsigned index = 0; index < length; ++index)
    {
        if (login[index] <= 0x1f) /* not printable */
            return (1);
        
        /* hashing algorithm - not working */
        unsigned eax, ecx, edx;

        eax = (int) login[index];
        ecx = eax;
        ecx ^= hash;
        edx = 0x88233b2b;
        eax = ecx;
        edx = eax * edx;
        eax = ecx;
        eax -= edx;
        eax >>= 1;
        eax += edx;
        eax >>= 0xa;
        eax *= 0x539;
        edx = ecx;
        edx -= eax;
        eax = edx;
        
        hash += eax;
    }

    if (hash != serial)
        return (1);
    
    return (0);
}

int main()
{
    char login[32 /* 0x4c - 0x2c */];
    unsigned serial;

    puts("***********************************");
    puts("*\t\tlevel06\t\t  *");
    puts("***********************************");

    printf("-> Enter Login: ");
    fgets(login, 32 /* 0x20 */, stdin);
    
    puts("***********************************");
    puts("***** NEW ACCOUNT DETECTED ********");

    printf("-> Enter Serial: ");
    scanf("%u", &serial);

    int ok = auth(login, serial);
    if (ok == 0)
    {
        puts("Authenticated!");
        system("/bin/sh");
    }

    return (ok != 0);
}
