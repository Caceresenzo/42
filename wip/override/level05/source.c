#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IS_UPPER(chr) (chr > '@' /* 0x40 */ && chr <= 'Z' /* 0x5a */)
#define TO_LOWER(chr) (chr ^ 0x20)

void main()
{
    unsigned index = 0; /* 0x8c */

    char buffer[100 /* 0x8c - 0x28 */];
    fgets(buffer, 100 /* 0x64 */, stdin);

    index = 0;
    while (index < strlen(buffer))
    {
        char chr = buffer[index];

        if (IS_UPPER(chr))
        {
            chr = TO_LOWER(chr);
            buffer[index] = chr;
        }

        ++index;
    }

    printf(buffer);
    exit(0);
}
