#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/prctl.h>

/* only available on 32bit systems */
#ifndef ORIG_EAX
# define ORIG_EAX 11
#endif

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

void enable_timeout_cons()
{
    signal(SIGALRM /* 0xe */, &prog_timeout);
    alarm(60 /* 0x3c */);
}

int main()
{
    char input[32 /* 0x20 */];

    pid_t pid = fork();
    memset(input, 0, sizeof(input));

    int wstatus = 0;
    int ptrace_eax = 0;

    if (pid == 0) /* child */
    {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME /* 0x0 */, 0, NULL, NULL);
        puts("Give me some shellcode, k");
        gets(input);
    }
    else
    {
        while (1)
        {
            wait(&wstatus);

            if (WIFEXITED(wstatus) || WIFSIGNALED(wstatus))
            {
                puts("child is exiting...");
                break ;
            }

            ptrace_eax = ptrace(PTRACE_PEEKUSER /* 0x3 */, pid, ORIG_EAX * 4 /* 0x2c */, NULL);
            if (ptrace_eax == SYS_execve /* 0xb */)
            {
                puts("no exec() for you");
                kill(pid, SIGKILL /* 0x9 */);
            }
        }
    }
}
