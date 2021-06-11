/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 00:35:03 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/11 00:35:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool
	file_open(int *fd, const char *path, int flags)
{
	*fd = open(path, flags, 0777);
	if (*fd == -1)
	{
		perror(path);
		return (false);
	}
	return (true);
}
