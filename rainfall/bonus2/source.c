#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int language = 0;

int greetuser(char name[])
{
    char message[72 /* 0x48 */];

    if (language == 1)
        strcpy(message, "Hyvää päivää ");
    else if (language == 2)
        strcpy(message, "Goedemiddag! ");
    else
        strcpy(message, "Hello ");

    strcat(message, name);
    return (puts(message));
}

int main(int argc, char const *argv[])
{
    char buffer[72 /* (0x12 - 1) * 4 */];

    if (argc != 3)
        return (1);

    memset(buffer, 0, sizeof(buffer));

    strncpy(buffer, argv[1], 40 /* 0x28 */);
    strncpy(buffer + 40, argv[2], 32 /* 0x20 */);

    char *lang = getenv("LANG");
    if (lang)
    {
        if (!memcmp(lang, "fi", 2))
            language = 1;
        else if (!memcmp(lang, "nl", 2))
            language = 2;
    }

    return (greetuser(buffer));
}