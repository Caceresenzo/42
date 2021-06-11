/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 23:37:39 by ecaceres          #+#    #+#             */
/*   Updated: 2021/06/10 23:37:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int
	pipex(t_pipex_params params)
{
	t_pipex_internal	internal;

	if (!pipex_init(&params, &internal))
		return (pipex_destroy(&internal, 1));
	if (!pipex_find_files(&internal))
		return (pipex_destroy(&internal, 1));
	if (!file_open(&internal.in, params.in, O_RDONLY))
		return (pipex_destroy(&internal, 1));
	if (!file_open(&internal.out, params.out, O_WRONLY | O_CREAT | O_TRUNC))
		return (pipex_destroy(&internal, 1));
	if (!pipex_open_pipes(&internal))
		return (pipex_destroy(&internal, 1));
	pipex_debug(&internal);
	return (pipex_destroy(&internal, 0));
}
