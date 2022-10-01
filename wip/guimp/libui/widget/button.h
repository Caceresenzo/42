/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:45:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:45:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_BUTTON_H
# define WIDGET_BUTTON_H

# include "../ui.h"

typedef enum e_ui_button_state
{
	UI_BUTTON_STATE_NONE,
	UI_BUTTON_STATE_HOVER,
	UI_BUTTON_STATE_PRESSED
} t_ui_button_state;

typedef struct s_ui_button
{
	t_ui_widget super;
	t_ui_button_state state;
	int color;
	int pressed_color;
} t_ui_button;

t_ui_button*
ui_button_new(void);

bool
ui_button_set_state(t_ui_button *button, t_ui_button_state state);

void
ui_button_size(t_ui_button *button, void *data);

void
ui_button_draw(t_ui_button *button, void *data);

int
ui_button_event(t_ui_button *button, t_ui_event_base *event, void *data);

#endif
