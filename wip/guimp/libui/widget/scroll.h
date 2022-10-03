/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_SCROLL_H
# define WIDGET_SCROLL_H

# include "../ui.h"

typedef enum e_ui_scrollbar_policy
{
	UI_SCROLLBAR_POLICY_ALWAYS = 1,
	UI_SCROLLBAR_POLICY_AS_NEEDED,
	UI_SCROLLBAR_POLICY_NEVER,
} t_ui_scrollbar_policy;

typedef struct s_ui_scroll_bar
{
	int offset;
	t_ui_scrollbar_policy policy;
} t_ui_scroll_bar;

typedef struct s_ui_scroll
{
	t_ui_widget super;
	t_ui_scroll_bar vertical;
} t_ui_scroll;

t_ui_scroll*
ui_scroll_new(void);

void
ui_scroll_size(t_ui_scroll *widget, void *data);

void
ui_scroll_draw(t_ui_scroll *widget, void *data);

void
ui_scroll_event(t_ui_scroll *widget, t_ui_event_base *event, void *data);

#endif
