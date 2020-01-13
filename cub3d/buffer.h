/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:07:30 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 11:07:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H

# include <stddef.h>

# include "libft/libft.h"

typedef struct	s_buffer
{
	size_t		length;
	char		*data;
}				t_buffer;

t_buffer		*buffer_create(size_t length);
void			buffer_destroy(t_buffer **buffer_ptr);

size_t			buffer_blit(t_buffer *buffer, unsigned char *s, size_t offset,
							size_t length);

size_t			buffer_write_ascii(t_buffer *buffer, char *s, size_t offset,
									size_t length);
size_t			buffer_write_uint_32_le(t_buffer *buffer, unsigned int value,
									size_t offset);
size_t			buffer_write_int_32_le(t_buffer *buffer, int value,
									size_t offset);

size_t			buffer_write_uint_16_le(t_buffer *buffer, unsigned int value,
									size_t offset);

void			buffer_fill(t_buffer *buffer, unsigned char value,
							size_t start, size_t end);

#endif
