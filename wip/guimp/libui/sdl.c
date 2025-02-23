/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:26:28 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:26:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void
sdl_abort(const char *function)
{
	printf("%s: %s\n", function, SDL_GetError());
	abort();
}

SDL_Color
sdl_as_color(int color)
{
	return (*((SDL_Color*)&color));
}
