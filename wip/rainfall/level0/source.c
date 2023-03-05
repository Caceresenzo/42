#define _GNU_SOURCE
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (atoi(argv[1]) == 423)
    {
        // get file's group owner
        gid_t gid = getegid();
        
        // get file's user owner
        uid_t uid = geteuid();

        // set process group owner
        setresgid(gid, gid, gid);
        
        // set process file owner
        setresuid(uid, uid, uid);

        char *const cmd[] = {
            "/bin/sh",
            NULL
        };

        execv(cmd[0], cmd);
    }
    else
        fwrite("No !\n", 1, 5, stdout);

    return (0);
}
