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
	UI_EVENT_TYPE_MOUSE_MOTION = 1,
	UI_EVENT_TYPE_MOUSE_PRESSED,
	UI_EVENT_TYPE_MOUSE_RELEASED,
	UI_EVENT_TYPE_MOUSE_WHEEL,
} t_ui_event_type;

typedef struct s_ui_event_base
{
	t_ui_event_type type;
	t_ui_window *window;
} t_ui_event_base;

typedef struct s_ui_event_mouse
{
	t_ui_event_base base;
	t_vector2i position;
} t_ui_event_mouse;

typedef struct s_ui_event_mouse_motion
{
	t_ui_event_base base;
	t_vector2i position;
	t_vector2i relative;
} t_ui_event_mouse_motion;

typedef enum s_ui_event_mouse_state
{
	UI_EVENT_MOUSE_STATE_PRESSED,
	UI_EVENT_MOUSE_STATE_RELEASED,
} t_ui_event_mouse_state;

typedef struct s_ui_event_mouse_button
{
	t_ui_event_base base;
	t_vector2i position;
	int button;
	t_ui_event_mouse_state state;
} t_ui_event_mouse_button;

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
	int
	(*code)(t_ui_widget*, const t_ui_event_base*, void*);
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

/* Continue to go deeper. */
# define UI_EVENT_CONTINUE 0

/* Mark event as consumed, and do not notify parents. */
# define UI_EVENT_CONSUME 1

#endif
