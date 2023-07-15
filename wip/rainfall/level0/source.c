#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (atoi(argv[1]) == 423)
    {
        char *const sh = strdup("/bin/sh");
        char *const cmd[] = {
            sh,
            NULL
        };

        /* get file's effective group owner */
        gid_t gid = getegid();
        
        /* get file's effective user owner */
        uid_t uid = geteuid();

        /* set process's effective group owner */
        setresgid(gid, gid, gid);
        
        /* set process effective file owner */
        setresuid(uid, uid, uid);

        execv("/bin/sh", cmd);
    }
    else
        fwrite("No !\n", 1, 5, stderr);

    return (0);
}
