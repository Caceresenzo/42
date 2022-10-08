/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:45:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:45:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_checkbox_H
# define WIDGET_checkbox_H

# include "../ui.h"

typedef struct s_ui_checkbox
{
	t_ui_widget super;
	bool checked;
	char *text;
} t_ui_checkbox;

t_ui_checkbox*
ui_checkbox_new(const char *text);

void
ui_checkbox_set_text(t_ui_checkbox *checkbox, const char *text);

void
ui_checkbox_set_checked(t_ui_checkbox *checkbox, bool value);

void
ui_checkbox_toggle(t_ui_checkbox *checkbox);

void
ui_checkbox_size(t_ui_checkbox *checkbox, void *data);

void
ui_checkbox_draw(t_ui_checkbox *checkbox, void *data);

void
ui_checkbox_describe(t_ui_checkbox *checkbox, char *buffer, void *data);

int
ui_checkbox_event(t_ui_scrollbar *this, t_ui_event_base *event, void *data);

#endif
