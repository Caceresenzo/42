/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scrollbar.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_SCROLLBAR_H
# define WIDGET_SCROLLBAR_H

# include "../ui.h"

typedef enum e_ui_scrollbar_orientation
{
	UI_SCROLLBAR_ORIENTATION_HORIZONTAL = 1,
	UI_SCROLLBAR_ORIENTATION_VERTICAL,
} t_ui_scrollbar_orientation;

typedef enum e_ui_scrollbar_policy
{
	UI_SCROLLBAR_POLICY_ALWAYS = 1,
	UI_SCROLLBAR_POLICY_AS_NEEDED,
	UI_SCROLLBAR_POLICY_NEVER,
} t_ui_scrollbar_policy;

typedef struct s_ui_scrollbar
{
	t_ui_widget super;
	t_ui_scrollbar_orientation orientation;
	t_ui_scrollbar_policy policy;
	int max;
	int offset;
	bool visible;
	bool hovered;
	struct
	{
		int position;
		int size;
		int margin;
	} thumb;
	struct
	{
		t_ui_widget_function_int scroll;
	} on;
} t_ui_scrollbar;

t_ui_scrollbar*
ui_scrollbar_new(t_ui_scrollbar_orientation orientation);

void
ui_scrollbar_set_max(t_ui_scrollbar *scrollbar, int max);

void
ui_scrollbar_set_offset(t_ui_scrollbar *widget, int offset);

int
ui_scrollbar_get_component(t_ui_scrollbar *this, t_vector2i vector);

void
ui_scrollbar_describe(t_ui_scrollbar *this, char *buffer, void *data);

void
ui_scrollbar_size(t_ui_scrollbar *widget, void *data);

void
ui_scrollbar_draw(t_ui_scrollbar *widget, void *data);

int
ui_scrollbar_event(t_ui_scrollbar *widget, t_ui_event_base *event, void *data);

void
ui_scrollbar_on_scroll_call(t_ui_scrollbar *this);

#endif
