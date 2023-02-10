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
#include <errno.h>

#include "ft_ssl.h"

static flags_t flags = {
	.stdin_ = false,
	.quiet = false,
	.reverse = false,
	.string = NULL
};

static algorithm_t algorithms[] = {
	{
		.name = "md5",
		.context_size = sizeof(md5_context_t),
		.digest_size = 16,
		.begin = (void*)md5_begin,
		.update = (void*)md5_update,
		.end = (void*)md5_end,
	},
	{
		.name = "sha256",
		.context_size = sizeof(sha256_context_t),
		.digest_size = 32,
		.begin = (void*)sha256_begin,
		.update = (void*)sha256_update,
		.end = (void*)sha256_end,
	},
	{
		.name = "sha224",
		.context_size = sizeof(sha224_context_t),
		.digest_size = 28,
		.begin = (void*)sha224_begin,
		.update = (void*)sha224_update,
		.end = (void*)sha224_end,
	},
	{
		.name = "sha512",
		.context_size = sizeof(sha512_context_t),
		.digest_size = 64,
		.begin = (void*)sha512_begin,
		.update = (void*)sha512_update,
		.end = (void*)sha512_end,
	},
	{
		.name = "sha384",
		.context_size = sizeof(sha384_context_t),
		.digest_size = 48,
		.begin = (void*)sha384_begin,
		.update = (void*)sha384_update,
		.end = (void*)sha384_end,
	},
	{ 0, 0, 0, 0, 0, 0, }
};

#define PROGRAM "ft_ssl"
#define FILE_STDIN "-"
#define BUFFER_SIZE 81924096

int usage(void)
{
	printf("usage: " PROGRAM " command [flags] [file/string]\n");
	return (EXIT_SUCCESS);
}

int invalid_command(const char *command)
{
	printf(PROGRAM ": Error: '%s' is an invalid command.\n", command);

	printf("\nCommands:\n");
	for (algorithm_t *algorithm = algorithms; algorithm->name; ++algorithm)
		printf("%s\n", algorithm->name);

	printf("\nFlags:\n");
	printf("-p -q -r -s\n");

	return (EXIT_FAILURE);
}

algorithm_t* parse_command(const char *command)
{
	for (algorithm_t *algorithm = algorithms; algorithm->name; ++algorithm)
	{
		if (ft_strcmp(algorithm->name, command) == 0)
			return (algorithm);
	}

	return (NULL);
}

int parse_flags(int argc, const char **argv)
{
	int index;
	for (index = 0; index < argc; ++index)
	{
		const char *arg = argv[index];

		if (ft_strcmp("-p", arg) == 0)
			flags.stdin_ = true;
		else if (ft_strcmp("-q", arg) == 0)
			flags.quiet = true;
		else if (ft_strcmp("-r", arg) == 0)
			flags.reverse = true;
		else if (ft_strcmp("-s", arg) == 0)
		{
			flags.string = argv[++index];

			if (!flags.string)
			{
				flags.string = "";
				break;
			}
		}
		else
			break;
	}

	return (index);
}

void digest_to_string(algorithm_t *algorithm, unsigned char *digest, char *hash)
{
	for (unsigned i = 0; i < algorithm->digest_size; ++i)
		sprintf(hash + (i * 2), "%02x", digest[i]);
}

void process_stdin_echo(algorithm_t *algorithm)
{
	char context[algorithm->context_size];
	unsigned char digest[algorithm->digest_size];
	char hash[algorithm->digest_size * 2 + 1];

	if (!flags.quiet)
	{
		printf("(\"");
		fflush(stdout);
	}

	char buffer[8192 * 8];
	ssize_t code;

	algorithm->begin((void*)context);
	while ((code = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
	{
		algorithm->update((void*)context, buffer, code);

		for (ssize_t index = 0; index < code; ++index)
		{
			char chr = buffer[index];
			if (chr != '\n' && chr != '\r')
				write(STDOUT_FILENO, &chr, 1);
		}
	}
	algorithm->end((void*)context, digest);

	digest_to_string(algorithm, digest, hash);

	if (!flags.quiet)
		printf("\")= %s\n", hash);
	else
		printf("\n%s\n", hash);
}

void process_stdin(algorithm_t *algorithm)
{
	char context[algorithm->context_size];
	unsigned char digest[algorithm->digest_size];
	char hash[algorithm->digest_size * 2 + 1];

	char buffer[8192 * 8];
	ssize_t code;

	algorithm->begin((void*)context);
	while ((code = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0)
		algorithm->update((void*)context, buffer, code);
	algorithm->end((void*)context, digest);

	digest_to_string(algorithm, digest, hash);

	if (!flags.quiet)
		printf("(stdin)= %s\n", hash);
	else
		printf("%s\n", hash);
}

void process_string(algorithm_t *algorithm)
{
	char context[algorithm->context_size];
	unsigned char digest[algorithm->digest_size];
	char hash[algorithm->digest_size * 2 + 1];

	algorithm->begin((void*)context);
	algorithm->update((void*)context, flags.string, ft_strlen(flags.string));
	algorithm->end((void*)context, digest);

	digest_to_string(algorithm, digest, hash);

	if (!flags.quiet)
	{
		if (flags.reverse)
			printf("%s \"%s\"\n", hash, flags.string);
		else
			printf("%s (\"%s\") = %s\n", algorithm->name, flags.string, hash);
	}
	else
		printf("%s\n", hash);
}

void process_file(algorithm_t *algorithm, const char *file)
{
	int fd = STDIN_FILENO;
	if (ft_strcmp(file, FILE_STDIN))
		fd = open(file, O_RDONLY);

	if (fd == -1)
	{
		const char *error = strerror(errno);
		printf(PROGRAM ": %s: %s: %s\n", algorithm->name, file, error);
		return;
	}

	char buffer[8192 * 8];
	ssize_t code;

	char context[algorithm->context_size];
	unsigned char digest[algorithm->digest_size];
	char hash[algorithm->digest_size * 2 + 1];

	algorithm->begin((void*)context);
	while ((code = read(fd, buffer, sizeof(buffer))) > 0)
		algorithm->update((void*)context, buffer, code);
	algorithm->end((void*)context, digest);

	digest_to_string(algorithm, digest, hash);

	if (!flags.quiet)
	{
		if (flags.reverse)
			printf("%s %s\n", hash, file);
		else
			printf("%s (%s) = %s\n", algorithm->name, file, hash);
	}
	else
		printf("%s\n", hash);

	if (fd != STDIN_FILENO)
		close(fd);
}

int main(int argc, const char **argv)
{
	if (argc < 2)
		return (usage());

	const char *command = argv[1];
	algorithm_t *algorithm = parse_command(command);
	if (!algorithm)
		return (invalid_command(command));

	int file_index = parse_flags(argc - 2, argv + 2) + 2;

	if (flags.stdin_)
		process_stdin_echo(algorithm);

	if (flags.string)
		process_string(algorithm);

	int index;
	for (index = file_index; index < argc; ++index)
	{
		const char *file = argv[index];
		process_file(algorithm, file);
	}

	if (file_index == index && !flags.stdin_ && !flags.string)
		process_stdin(algorithm);

	return (EXIT_SUCCESS);
}
