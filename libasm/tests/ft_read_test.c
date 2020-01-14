/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 14:55:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/02 14:55:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

static void
	look_for_chars(char buffer[2][11])
{
	size_t	index;

	index = 0;
	while (index < 11)
	{
		if (buffer[0][index] == '\n')
			buffer[0][index] = 'n';
		if (buffer[0][index] == '\t')
			buffer[0][index] = 't';
		if (buffer[1][index] == '\n')
			buffer[1][index] = 'n';
		if (buffer[1][index] == '\t')
			buffer[1][index] = 't';
		index++;
	}
	buffer[0][10] = '\0';
	buffer[1][10] = '\0';
}

void
	test_ft_read(void)
{
	int			fds[2];
	char		buffer[2][11];
	ssize_t		byte_read[2];
	size_t		index;

	list_display_header();
	fds[0] = open("tests/ft_read_test.c", O_RDONLY);
	fds[1] = open("tests/ft_read_test.c", O_RDONLY);
	index = 0;
	while (index < 100)
	{
		bzero(buffer, sizeof(buffer));
		byte_read[0] = ft_read(fds[0], buffer[0], 10);
		byte_read[1] = read(fds[1], buffer[1], 10);
		look_for_chars(buffer);
		list_display_result("ft_read", buffer[0], buffer[1], LIST_AS_STRING);
		index++;
	}
	printf("\n");
}
