#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void log_wrapper(FILE *log_file, const char *action, const char *file_name)
{
    char buffer[255 /* 0xff */];

    strcpy(buffer, action);
    snprintf(buffer + strlen(buffer), 254 /* 0xfe */ - strlen(buffer), file_name);
    buffer[strcspn(buffer, "\n")] = '\0';

    fprintf(log_file, "LOG: %s\n", buffer);
}

int main(int argc, char const *argv[] /* rbp-0xa0 */)
{
    if (argc != 2)
        printf("Usage: %s filename\n", argv[0]);
    
    FILE *log_file /* rbp-0x88 */ = fopen("./backups/.log", "w");
    if (!log_file)
    {
        printf("ERROR: Failed to open %s\n", "./backups/.log");
        exit(1);
    }

    log_wrapper(log_file, "Starting back up: ", argv[1]);
    
    FILE *input_file /* rbp-0x80 */ = fopen(argv[1], "r");
    if (!input_file)
    {
        printf("ERROR: Failed to open %s\n", argv[1]);
        exit(1);
    }

    char buffer[100 /* 0x64 */] /* rbp-0x70 */;
    strcpy(buffer, "./backups/");
    strncat(buffer, argv[1], 99 /* 0x63 */ - strlen(buffer));

    int output_fd /* rbp-0x78 */ = open(buffer, O_WRONLY | O_CREAT | O_EXCL /* 0xc1 */, 0660 /* 0x1b0 */);
    if (output_fd < 0)
    {
        printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
        exit(1);
    }

    while (1)
    {
        char chr /* rbp-0x71 */ = fgetc(input_file);
        if (chr == -1 /* 0xff */)
            break;
        
        write(output_fd, &chr, 1);
    }

    log_wrapper(log_file, "Finished back up ", argv[1]);

    fclose(input_file);
    close(output_fd);

    return (0);
}
