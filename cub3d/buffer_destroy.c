/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:22:56 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 12:22:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

void
	buffer_destroy(t_buffer **buffer_ptr)
{
	free((*buffer_ptr)->data);
	(*buffer_ptr)->length = 0;
	free(*buffer_ptr);
	*buffer_ptr = NULL;
}
