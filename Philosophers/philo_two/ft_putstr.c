/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:38:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:38:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	ft_putstr(char *str)
{
	ft_putstr_fd(str, FD_OUT);
}

void
	ft_putstr_errno(char *msg)
{
	ft_putstr_fd(msg, FD_ERR);
	ft_putstr_fd(" (", FD_ERR);
	ft_putstr_fd(strerror(errno), FD_ERR);
	ft_putstr_fd(")\n", FD_ERR);
}

void
	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}
