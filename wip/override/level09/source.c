#include <stdio.h>
#include <string.h>

struct msg {
    char content[140 /* 0xc0 (handle_msg rsp) - 40 (username) - 4 (max_length) - 8 (gcc)*/];
    char username[40 /* 0x28 */];
    unsigned length;
};

void secret_backdoor()
{
    char buffer[128 /* 0x80 */];

    fgets(buffer, 128 /* 0x80 */, stdin);

    system(buffer);
}

void set_username(struct msg *msg)
{
    char buffer[128 /* 0x80 */];
    memset(buffer, 0, sizeof(buffer));
    
    puts(">: Enter your username");
    printf(">>: ");

    fgets(buffer, 128 /* 0x80 */, stdin);

    for (unsigned index = 0; index <= 0x28 && buffer[index]; ++index)
        msg->username[index] = buffer[index];

    printf(">: Welcome, %s", msg->username);
}

void set_msg(struct msg *msg)
{
    char buffer[1024 /* 0x400 */];
    memset(buffer, 0, sizeof(buffer));

    puts(">: Msg @Unix-Dude");
    printf(">>: ");

    fgets(buffer, 1024 /* 0x400 */, stdin);
    strncpy(msg->content, buffer, msg->length);
}

void handle_msg()
{
    struct msg msg;

    memset(msg.username, 0, sizeof(msg.username));
    msg.length = 140 /* 0x8c */;

    set_username(&msg);
    set_msg(&msg);

    puts(">: Msg sent!");
}

int main(int argc, char const *argv[])
{
    puts(
        "--------------------------------------------\n"
        "|   ~Welcome to l33t-m$n ~    v1337        |\n"
        "--------------------------------------------"
    );

    handle_msg();

    return (0);
}
