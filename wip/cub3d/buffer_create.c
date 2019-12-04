/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:09:39 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 11:09:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

t_buffer
	*buffer_create(size_t length)
{
	t_buffer *buffer;

	if (!(buffer = malloc(sizeof(t_buffer))))
		return (NULL);
	buffer->length = length;
	buffer->data = ft_calloc(length, sizeof(char));
	if (buffer->data == NULL)
	{
		free(buffer);
		buffer = NULL;
	}
	return (buffer);
}
