/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_exporter_bmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:03:45 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 17:03:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	mlx_export_bmp(t_engine *engine)
{
	int		fd;
	int		result;

	fd = open(EXPORT_FILE, 664);
	if (fd < 0)
		engine_handle_error_w_errno(E("Failed to open export file: "
				EXPORT_FILE));
	render_scene(engine);
	result = bmp_encode(fd, engine->canvas);
	if (result)
		ft_putendl_fd("Exported file: "EXPORT_FILE, OUT);
	else
		engine_handle_error_w_errno("Failed to export rendered image: "\
				EXPORT_FILE);
	close(fd);
}
