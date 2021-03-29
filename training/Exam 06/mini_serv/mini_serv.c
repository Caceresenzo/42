#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mini_serv.h"

typedef unsigned char byte;

int sockfd = -1;
int client_ids_increment = 0;
t_list *clients = NULL;

char*
str_join(char *buf, char *add)
{
	char *newbuf;
	int len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = (char*)malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

int
extract_message(char **buf, char **msg)
{
	char *newbuf;
	int i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = (char*)calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

static void
free_client(void *ptr)
{
	t_client *client = (t_client*)ptr;

	close(client->fd);
	free(client->buffer);
	list_clear(&client->messages, istr_unuse_v);
	free(client);
}

static int
fatal_error()
{
	if (sockfd != -1)
		close(sockfd);

	if (clients)
		list_clear(&clients, free_client);

	printf("Fatal error\n");
	return (1);
}

static int
do_call_fatal_error(const char *function, int line)
{
	printf("%s:%d -- ", function, line);
	return (fatal_error());
}

#define fatal_error() do_call_fatal_error(__FUNCTION__, __LINE__)

static bool
broadcast(char *str, t_client *avoid)
{
	t_instanced_string *istr = istr_wrap(str);

	if (!str)
		return (false);

	istr_use(istr);

	t_list *node = clients;
	while (node)
	{
		t_client *client = (t_client*)node->data;

		if (avoid == client)
			;
		else if (!list_add(&client->messages, istr))
		{
			istr_unuse(istr);
			return (false);
		}
		else
		{
			istr_use(istr);
		}

		node = node->next;
	}

	istr_unuse(istr);
	return (true);
}

static bool
broadcast_join(t_client *client)
{
	char buffer[255];
	sprintf(buffer, "server: client %d just arrived\n", client->id);

	return (broadcast(buffer, client));
}

static bool
broadcast_message(t_client *client, char *msg)
{
	size_t len = strlen(msg);
	char buffer[255 + len];

	if (len && msg[len - 1] == '\n')
		msg[len - 1] = '\0';

	sprintf(buffer, "client %d: %s\n", client->id, msg);

	return (broadcast(buffer, client));
}

static bool
broadcast_leave(t_client *client)
{
	char buffer[255];
	sprintf(buffer, "server: client %d just left\n", client->id);

	return (broadcast(buffer, client));
}

int
main()
{
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		return (fatal_error());

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(8081);

	if ((bind(sockfd, (const struct sockaddr*)&servaddr, sizeof(servaddr))) != 0)
		return (fatal_error());

	if (listen(sockfd, 10) != 0)
		return (fatal_error());

	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);

	int highest = sockfd + 1;

	while (true)
	{
		fd_set read_fds = fds;
		fd_set write_fds = fds;

//		for (int i = 0; i < 10; i++)
//			printf("%d", FD_ISSET(i, &except_fds));
//		printf("\n");

		if (select(highest, &read_fds, &write_fds, NULL, NULL) == -1)
			return (fatal_error());

		if (FD_ISSET(sockfd, &read_fds))
		{
			int fd = accept(sockfd, NULL, NULL);

			if (fd == -1)
				return (fatal_error());

			t_client *client = (t_client*)malloc(sizeof(t_client));

			if (!client)
			{
				close(fd);
				return (fatal_error());
			}

			client->id = client_ids_increment++;
			client->fd = fd;
			client->messages = NULL;
			client->buffer = NULL;
			client->send_up_to = 0;

			if (!list_add(&clients, client))
			{
				free_client(client);
				return (fatal_error());
			}

			if (!broadcast_join(client))
				return (fatal_error());

			FD_SET(fd, &fds);

			if (highest <= fd)
				highest = fd + 1;
		}

		for (int i = 0; i < highest; i++)
		{
			if (i == sockfd)
				continue;

			bool for_read = FD_ISSET(i, &read_fds);
			bool for_write = FD_ISSET(i, &write_fds);

			if (!for_read && !for_write)
				continue;

			t_client *client = NULL;
			{
				t_list *node = clients;
				while (node)
				{
					t_client *x = (t_client*)node->data;
					if (x->fd == i)
					{
						client = x;
						break;
					}

					node = node->next;
				}
			}

			if (!client)
			{
				printf("warning, no client found for fd = %d\n", i);
				continue;
			}

			if (for_read)
			{
				char buffer[256];
				int r = recv(client->fd, buffer, sizeof(buffer) - 1, 0);

				if (r < 1)
				{
					FD_CLR(client->fd, &fds);

					if (!broadcast_leave(client))
						return (fatal_error());

					list_delete_first(&clients, client, free_client);

					continue;
				}

				buffer[r] = '\0';
				client->buffer = str_join(client->buffer, buffer);

				r = 1;
				while (r > 0)
				{
					char *line;
					r = extract_message(&client->buffer, &line);

					if (r)
					{
						broadcast_message(client, line);

						if (strcmp("/quit", line) == 0)
						{
							free(line);
							return (fatal_error());
						}

						free(line);
					}
				}

				if (r == -1)
					return (fatal_error());
			}

			if (for_write && client->messages)
			{
				t_instanced_string *first = (t_instanced_string *)client->messages->data;

				char *to_send = (char*)first->data + client->send_up_to;
				size_t to_send_len = first->len - client->send_up_to;

				int r = send(client->fd, to_send, to_send_len, 0);

				if (r < 1)
				{
					FD_CLR(client->fd, &fds);

					if (!broadcast_leave(client))
						return (fatal_error());

					list_delete_first(&clients, client, free_client);

					continue;
				}

				if (r == to_send_len)
				{
					list_delete_first(&client->messages, first, istr_unuse_v);
					client->send_up_to = 0;
				}
				else
					client->send_up_to = r;
			}
		}
	}
}
