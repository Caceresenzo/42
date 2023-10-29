#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    char buffer[40];
    int x;

    x = atoi(argv[1]);
    if (x < 10)
    {
        memcpy(buffer, argv[2], x * 4);

        if (x == 1464814662 /* 0x574f4c46 */)
            execl("/bin/sh", "sh", NULL);
        
        return (0);
    }
    
    return (1);
}