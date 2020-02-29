/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_atoi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:21:26 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 16:21:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	x_atoi(char *str, int *err)
{
	int result;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	*err = *str != '\0';
	return (result);
}
