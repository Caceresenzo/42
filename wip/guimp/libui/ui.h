/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:39:09 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 19:39:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include <assert.h>
# include <stdbool.h>

# include "../liblist/list.h"

# include "sdl.h"
# include "math.h"
# include "utility.h"
# include "optional.h"

typedef struct s_error
{
	bool present;
	const char *message;
} t_ui_error;

typedef struct s_ui_application t_ui_application;
typedef struct s_ui_window t_ui_window;
typedef struct s_ui_widget t_ui_widget;
typedef struct s_ui_widget_descriptor t_ui_widget_descriptor;
typedef struct s_style t_style;

typedef struct s_ui_widget_function t_ui_widget_function;
typedef struct s_ui_widget_function_event t_ui_widget_function_event;
typedef struct s_ui_event_base t_ui_event_base;

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

typedef struct s_style
{
	t_optional_int width;
	t_optional_int min_width;
	t_optional_int max_width;
	t_optional_int height;
	t_optional_int min_height;
	t_optional_int max_height;
	t_optional_color text_color;
	t_optional_color background_color;
} t_style;

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
	char *id;
	t_ui_window *window;
	t_ui_widget *parent;
	t_vector2i position;
	t_vector2i size;
	bool dirty;
	bool focusable;
	bool traversable;
	t_style style;
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

t_ui_application*
ui_application_new(void);

void
ui_application_destroy(t_ui_application *app);

t_ui_window*
ui_application_find_window(t_ui_application *app, uint32_t id);

void
ui_application_draw(t_ui_application *app);

t_ui_window*
ui_window_new(t_ui_application *app, t_vector2i position, t_vector2i size, uint32_t flags);

void
ui_window_destroy(t_ui_window *window);

const char*
ui_window_get_title(t_ui_window *window);

void
ui_window_set_title(t_ui_window *window, const char *title);

t_ui_widget*
ui_window_set_root(t_ui_window *window, t_ui_widget *widget);

void
ui_widget_add(t_ui_widget *parent, t_ui_widget *widget);

void
ui_window_draw(t_ui_window *window);

void
ui_window_dispatch(const t_ui_event_base *event);

t_ui_widget*
ui_window_find_by_id(t_ui_window *window, const char *id);

t_ui_widget*
ui_widget_new(t_ui_widget_descriptor *descriptor);

void
ui_widget_size(t_ui_widget *widget);

void
ui_widget_draw(t_ui_widget *widget);

void
ui_widget_set_id(t_ui_widget *widget, const char *id);

void
ui_widget_set_dirty(t_ui_widget *widget);

t_ui_widget*
ui_widget_find_by_id(t_ui_widget *widget, const char *id);

bool
ui_widget_is_inside(t_ui_widget *widget, t_vector2i point);

void
ui_widget_function_call(t_ui_widget *widget, t_ui_widget_function *function);

void
ui_widget_draw_call(t_ui_widget *widget);

void
ui_widget_size_call(t_ui_widget *widget);

void
ui_widget_event_call(t_ui_widget *widget, const t_ui_event_base *event);

bool
ui_font_load(t_ui_application *app, const char *path, int size);

void
ui_style_apply_size(t_ui_widget *widget);

void
ui_application_dump(t_ui_application *app);

void
ui_window_dump(t_ui_window *window);

void
ui_widget_dump(t_ui_widget *widget);

t_ui_error
ui_error_present(const char *message);

t_ui_error
ui_error_absent(void);

# include "widget/group.h"
# include "widget/container.h"
# include "widget/label.h"
# include "widget/image.h"
# include "widget/button.h"

#endif
