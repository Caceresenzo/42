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

typedef struct s_ui_widget_function t_ui_widget_function;
typedef struct s_ui_widget_function_event t_ui_widget_function_event;

typedef enum e_ui_event_type
{
	UI_EVENT_TYPE_MOUSE_MOVED = 1,
	UI_EVENT_TYPE_MOUSE_DRAGGED,
	UI_EVENT_TYPE_MOUSE_CLICKED,
	UI_EVENT_TYPE_MOUSE_ENTERED,
	UI_EVENT_TYPE_MOUSE_EXITED,
	UI_EVENT_TYPE_MOUSE_PRESSED,
	UI_EVENT_TYPE_MOUSE_RELEASED,
} t_ui_event_type;

typedef struct s_ui_event_base
{
	t_ui_event_type type;
	long timestamp;
	t_ui_window *window;
} t_ui_event_base;

typedef struct s_ui_event_mouse
{
	t_ui_event_base super;
	int x;
	int y;
	int button;
} t_ui_event_mouse;

typedef struct s_ui_event_mouse_wheel
{
	t_ui_event_base base;
	t_vector2i scroll;
} t_ui_event_mouse_wheel;

struct s_ui_widget_function
{
	void
	(*code)(t_ui_widget*, void*);
	void *data;
};

struct s_ui_widget_function_event
{
	void
	(*code)(t_ui_widget*, const t_ui_event_base*, void*);
	void *data;
};

struct s_ui_application
{
	const char *name;
	bool running;
	TTF_Font *font;
	bool exit_on_close;
	t_list windows;
};

struct s_ui_window
{
	t_ui_application *app;
	t_ui_widget *root;
	bool dirty;
	t_vector2i size;
	t_ui_widget *focused;
	t_ui_widget *hovered;
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
	bool focusable;
	bool traversable;
	t_list children;
	SDL_Surface *_surface;
};

struct s_ui_widget_descriptor
{
	const char *name;
	const size_t size;
	struct
	{
		t_ui_widget_function draw;
		t_ui_widget_function size;
		t_ui_widget_function_event event;
	} handlers;
};

#endif
