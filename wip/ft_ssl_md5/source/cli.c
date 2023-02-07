/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:57:49 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:57:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "ft_ssl.h"

static algorithm_t algorithms[] = {
	{
		.name = "md5",
		.context_size = sizeof(md5_context_t),
		.digest_size = 16,
		.begin = (void*)md5_begin,
		.update = (void*)md5_update,
		.end = (void*)md5_end,
	},
	{ 0, 0, 0, 0, 0, }
};

int main(int argc, char **argv)
{
	const char *command = argv[1];
	if (!command)
	{
		dprintf(2, "missing command\n");
		return (EXIT_FAILURE);
	}

	algorithm_t *algorithm = algorithms;
	while (algorithm->name)
	{
		if (strcmp(algorithm->name, command) == 0)
			break;

		++algorithm;
	}

	if (!algorithm->name)
	{
		dprintf(2, "unknown algorithm: `%s`\n", command);
		return (EXIT_FAILURE);
	}

	int fd = 1;

	const char *file = argv[2];
	if (file)
	{
		fd = open(file, O_RDONLY);

		if (fd == -1)
		{
			perror("open");
			return (EXIT_FAILURE);
		}
	}

	char context[algorithm->context_size];
	algorithm->begin((void*)context);

	char buffer[8096 * 8];
	ssize_t code;

	while ((code = read(fd, buffer, sizeof(buffer))) > 0)
		algorithm->update((void*)context, buffer, code);

	unsigned char digest[algorithm->digest_size];
	algorithm->end((void*)context, digest);

	for (unsigned i = 0; i < algorithm->digest_size; ++i)
		printf("%02x", digest[i]);
	printf("\n");

	close(fd);
	return (EXIT_SUCCESS);
}
