/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_quick.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 14:17:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/12/04 14:17:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char
	*e(const char *error)
{
	return (ft_strdup(error));
}

char
	*emalloc(const char *location)
{
	return (ft_strjoin("Failed to malloc() -->", location));
}
