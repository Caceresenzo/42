/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 00:20:32 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 00:20:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char
	*path_get(const char *bin)
{
	if (!bin)
		return (NULL);
	if (file_test_read(bin))
		return (ft_strdup(bin));
	return (NULL);
}
