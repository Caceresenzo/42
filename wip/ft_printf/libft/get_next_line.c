/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:27:24 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/06 15:27:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 128
#endif

unsigned char	*internal_gnl_store(unsigned char c, int force)
{
	static unsigned char	*stored = NULL;
	static size_t			stored_length = 0;
	unsigned char			*new;

	CHECK_MALLOC(new, (stored_length + 1 + force) * sizeof(char));
	if (stored != NULL)
	{
		ft_memcpy(new, stored, stored_length);
		free(stored);
	}
	if (c == '\n' || force)
	{
		new[stored_length] = '\0';
		new[stored_length + force] = '\0';
		stored = NULL;
		stored_length = 0;
		return (new);
	}
	new[stored_length] = c;
	stored_length++;
	stored = new;
	return (NULL);
}

int				internal_gnl_handle(unsigned char buffer[BUFFER_SIZE],
									size_t byte_read, char **return_line,
									size_t *offset)
{
	unsigned char	*line;
	int				force;

	while (*offset < BUFFER_SIZE)
	{
		force = *offset >= byte_read;
		line = internal_gnl_store(buffer[*offset], force);
		*offset += 1;
		if (line != NULL)
		{
			if (force)
				*offset = BUFFER_SIZE;
			*return_line = (char *)line;
			return (1 + force);
		}
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static unsigned char	buffer[BUFFER_SIZE];
	static size_t			byte_read = 0;
	static size_t			offset = BUFFER_SIZE;
	int						code;

	if (line == NULL)
		return (GNL_END_REACHED);
	*line = NULL;
	while (1)
	{
		if (offset == BUFFER_SIZE)
		{
			byte_read = read(fd, buffer, BUFFER_SIZE);
			offset = 0;
		}
		if (byte_read == (size_t)-1)
			return (GNL_ERROR);
		if ((code = internal_gnl_handle(buffer, byte_read, line, &offset)))
		{
			if (byte_read == 0 || code == 2)
				return (GNL_END_REACHED);
			return (GNL_READ);
		}
	}
}
