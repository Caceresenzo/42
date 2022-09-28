/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:14:24 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:14:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "math.h"
#include "../liblist/list.h"

typedef struct s_ui_application t_ui_application;
typedef struct s_ui_window t_ui_window;
typedef struct s_ui_widget t_ui_widget;
typedef struct s_ui_widget_descriptor t_ui_widget_descriptor;

struct s_ui_callback_draw
{
	void
	(*function)(t_ui_widget*, void*);
	void *data;
};

struct s_ui_callback_size
{
	void
	(*function)(t_ui_widget*, void*);
	void *data;
};

struct s_ui_application
{
	const char *name;
	TTF_Font *font;
	t_list windows;
};

struct s_ui_window
{
	t_ui_application *app;
	t_ui_widget *root;
	bool dirty;
	t_vector2i size;
	SDL_Window *_window;
};

struct s_ui_widget
{
	t_ui_widget_descriptor *descriptor;
	t_ui_window *window;
	t_ui_widget *parent;
	t_vector2i position;
	t_vector2i size;
	bool dirty;
	t_list children;
	struct s_ui_callback_draw draw_handler;
	struct s_ui_callback_size size_handler;
	SDL_Surface *_surface;
};

struct s_ui_widget_descriptor
{
	const char *name;
	const size_t size;
};

#endif
