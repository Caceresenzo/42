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

	fd = open(EXPORT_FILE, O_WRONLY | O_CREAT, 0664);
	if (fd < 0)
		engine_error_raison(e("Failed to open export file: "EXPORT_FILE));
	render_scene(engine);
	result = bmp_encode(fd, engine->canvas);
	close(fd);
	if (result)
	{
		if (BONUS)
			ft_putendl_fd("Exported file: "EXPORT_FILE, OUT);
	}
	else
		engine_error("Failed to export rendered image: "EXPORT_FILE);
}
