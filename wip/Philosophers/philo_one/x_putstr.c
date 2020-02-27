/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_putstr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:24:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:24:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	x_putstr(char *str)
{
	x_putstr_fd(str, OUT);
}

void
	x_putstr_fd(char *str, int fd)
{
	size_t	len;

	len = x_strlen(str);
	write(fd, str, len);
}
