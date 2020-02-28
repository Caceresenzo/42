/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_putnbr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:00:49 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 18:00:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	x_putnbr(long n)
{
	x_putnbr_fd(n, OUT);
}

void
	x_putnbr_fd(long n, int fd)
{
	if (n > 10)
		x_putnbr(n / 10);
	write(fd, &"0123456789"[n % 10], 1);
}
