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
typedef struct s_ui_widget_function_describe t_ui_widget_function_describe;
typedef struct s_ui_widget_function_hitscan_interceptor t_ui_widget_function_hitscan_interceptor;
typedef struct s_ui_widget_function_int t_ui_widget_function_int;
typedef struct s_ui_event_base t_ui_event_base;

struct s_ui_widget_function
{
	void
	(*code)(t_ui_widget*, void*);
	void *data;
};

# define UI_EVENT_CONSUME 1
# define UI_EVENT_CONTINUE 2

struct s_ui_widget_function_event
{
	int
	(*code)(t_ui_widget*, const t_ui_event_base*, void*);
	void *data;
};

struct s_ui_widget_function_describe
{
	void
	(*code)(t_ui_widget*, char*, void*);
	void *data;
};

struct s_ui_widget_function_hitscan_interceptor
{
	void
	(*code)(t_ui_widget*, t_vector2i*, void*);
	void *data;
};

struct s_ui_widget_function_int
{
	void
	(*code)(t_ui_widget*, int, void*);
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
	t_optional_color color;
	t_optional_color background_color;
	t_optional_color hover_color;
} t_style;

typedef struct s_font
{
	char *name;
	int size;
	TTF_Font *_font;
} t_font;

struct s_ui_application
{
	const char *name;
	bool running;
	t_font *font;
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
	bool managed;
	t_style style;
	t_list children;
	SDL_Surface *_surface;
};

# define UI_WIDGET_DESCRIPTOR_UNLIMITED_CHILDREN (-1)

struct s_ui_widget_descriptor
{
	const char *name;
	const size_t size;
	const int children_limit;
	struct
	{
		t_ui_widget_function_describe describe;
		t_ui_widget_function_hitscan_interceptor hitscan_interceptor;
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
	UI_EVENT_TYPE_MOUSE_WHEEL_MOVED,
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
	t_vector2i position;
	t_vector2i local;
	int button;
} t_ui_event_mouse;

typedef struct s_ui_event_mouse_wheel
{
	t_ui_event_base super;
	t_vector2i position;
	t_vector2i local;
	t_vector2i scroll;
} t_ui_event_mouse_wheel;

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
ui_window_draw(t_ui_window *window);

void
ui_window_dispatch(t_ui_event_base *event);

t_ui_widget*
ui_window_find_by_id(t_ui_window *window, const char *id);

t_ui_widget*
ui_widget_new(t_ui_widget_descriptor *descriptor);

bool
ui_widget_add(t_ui_widget *parent, t_ui_widget *widget);

void
ui_widget_size(t_ui_widget *widget);

void
ui_widget_draw(t_ui_widget *widget, bool blit_to_parent);

void
ui_widget_set_id(t_ui_widget *widget, const char *id);

void
ui_widget_set_dirty(t_ui_widget *widget);

t_ui_widget*
ui_widget_find_by_id(t_ui_widget *widget, const char *id);

bool
ui_widget_is_inside(t_ui_widget *widget, t_vector2i point);

t_ui_widget*
ui_widget_get_child(t_ui_widget *widget, int index);

void
ui_widget_function_call(t_ui_widget *widget, t_ui_widget_function *function);

void
ui_widget_function_int_call(t_ui_widget *widget, t_ui_widget_function_int *function, int value);

void
ui_widget_draw_call(t_ui_widget *widget);

void
ui_widget_size_call(t_ui_widget *widget);

int
ui_widget_event_call(t_ui_widget *widget, const t_ui_event_base *event);

void
ui_widget_hitscan_interceptor_call(t_ui_widget *widget, t_vector2i *point);

void
ui_widget_describe_call(t_ui_widget *widget, char *buffer);

bool
ui_font_load(t_ui_application *app, const char *path, int size);

t_vector2i
ui_font_size(t_font *font, char *text);

void
ui_font_draw(t_font *font, SDL_Surface *surface, char *text, t_vector2i position, int color);

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

bool
ui_event_type_is_mouse(t_ui_event_type type);

typedef struct s_ui_scrollbar t_ui_scrollbar;
typedef struct s_ui_viewport t_ui_viewport;

# include "widget/group.h"
# include "widget/container.h"
# include "widget/label.h"
# include "widget/image.h"
# include "widget/button.h"
# include "widget/canvas.h"
# include "widget/scrollbar.h"
# include "widget/viewport.h"
# include "widget/scroll.h"
# include "widget/checkbox.h"

#endif
