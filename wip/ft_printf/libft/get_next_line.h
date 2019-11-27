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

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"

# define GNL_READ 1
# define GNL_END_REACHED 0
# define GNL_ERROR -1

int		get_next_line(int fd, char **line);

void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
