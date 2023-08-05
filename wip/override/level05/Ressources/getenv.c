#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const* argv[])
{
    if (argc != 2)
    {
        printf("usage: %s <var name>\n", argv[0]);
        return (1);
    }

    char const *var_name = argv[1];
    char const *ptr = getenv(var_name);

    printf("%s=%s\n", var_name, ptr, ptr);
    printf("address: %p\n", var_name, ptr, ptr);
    return (0);
}
