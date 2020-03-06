/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:46:37 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/05 13:46:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	ft_putstr_fd(char *s, int fd)
{
	t_uchar		*str;

	if (!s)
		return ;
	str = (t_uchar *)s;
	while (*str)
		ft_putchar_fd(*str++, fd);
}
