#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *auth = NULL;
char *service = NULL;

int main()
{
    char input[128 /* 0x80 */];

    while (true)
    {
        printf("%p, %p \n", auth, service);
        
        if (fgets(input, 128 /* 0x80 */, stdin) == 0)
            break;
        
        if (strncmp("auth ", input, 5) == 0)
        {
            auth = malloc(4);
            *auth = 0;

            char *name = input + 5;
            if (strlen(input) - 1 < 30 /* 0x1e */)
                strcpy(auth, name);
        }
        else if (strncmp("reset", input, 5) == 0)
        {
            if (auth)
                free(auth);
        }
        else if (strncmp("service", input, 7) == 0)
            service = strdup(input + 7);
        else if (strncmp("login", input, 5) == 0)
        {
            if (auth[32] == 0)
                fwrite("Password:\n", 1, 10, stdout);
            else
                system("/bin/sh");
        }
    }

    return (0);
}