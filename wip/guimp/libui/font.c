/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 21:38:20 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/28 21:38:20 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

bool
ui_font_load(t_ui_application *app, const char *path, int size)
{
	app->font = TTF_OpenFont(path, size);
	if (!app->font)
		sdl_abort("TTF_OpenFont");
	return (true);
}
