/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_write_header.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:12:51 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 17:12:51 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	bmp_write_header(int fd, t_image *image)
{
	ft_putstr_fd("BM", fd);
	ft_putmem_fd("\x7a\x03\x00\x00\x00\x00\x00\x00", 8, fd);
	ft_putmem_fd("\x00\x00\x00\x00", 4, fd);
	ft_putmem_fd("\x00\x00\x00\x00", 4, fd);
}
