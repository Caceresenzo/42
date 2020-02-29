/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_strlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:24:42 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:24:42 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t
	x_strlen(char *str)
{
	char	*start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}
