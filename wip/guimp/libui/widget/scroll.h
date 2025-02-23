/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.h                                           :+:      :+:    :+:   */
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

typedef struct s_ui_scroll
{
	t_ui_widget super;
	t_ui_viewport* viewport;
	t_ui_scrollbar* vertical;
	t_ui_scrollbar* horizontal;
} t_ui_scroll;

t_ui_scroll*
ui_scroll_new(void);

void
ui_scroll_size(t_ui_scroll *widget, void *data);

void
ui_scroll_draw(t_ui_scroll *widget, void *data);

int
ui_scroll_event(t_ui_scroll *widget, t_ui_event_base *event, void *data);

#endif
