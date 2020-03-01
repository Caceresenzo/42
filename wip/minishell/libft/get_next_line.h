/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:27:31 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/06 15:27:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define GNL_READ 1
# define GNL_END_REACHED 0
# define GNL_ERROR -1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct		s_gnl_holder
{
	int				initialized;
	int				reached;
	unsigned char	buffer[BUFFER_SIZE];
	size_t			byte_read;
	size_t			offset;
	unsigned char	*stored;
	size_t			stored_length;
}					t_gnl_holder;

int					get_next_line(int fd, char **line);

#endif
