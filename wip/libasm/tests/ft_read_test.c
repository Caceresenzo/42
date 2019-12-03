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
#include "../libasm.h"

void
	test_ft_read(void)
{
	int			fds[2];
	char		buffer[11];
	ssize_t		byte_read;
	size_t		index;

	fds[0] = open("tests/ft_read_test.c", O_RDONLY);
	fds[1] = open("tests/ft_read_test.c", O_RDONLY);
	index = 0;
	while (index < 10)
	{
		printf("--------------\n");
		bzero(buffer, 11);
		byte_read = read(fds[0], buffer, 10);
		printf("read      : %zu -> \"%s\"\n", byte_read, buffer);
		bzero(buffer, 11);
		byte_read = ft_read(fds[1], buffer, 10);
		printf("ft_read   : %zu -> \"%s\"\n", byte_read, buffer);
		index++;
	}
}
