/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 00:31:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 00:31:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_GROUP_H
# define WIDGET_GROUP_H

# include "../ui.h"

typedef enum e_ui_group_direction {
	UI_GROUP_DIRECTION_NONE = 1,
	UI_GROUP_DIRECTION_VERTICAL,
	UI_GROUP_DIRECTION_HORIZONTAL
} t_ui_group_direction;

t_vector2i
ui_group_size(t_list *children, t_ui_group_direction direction);

void
ui_group_size_widget(t_ui_widget *widget, t_ui_group_direction direction);

void
ui_group_draw(t_list *children, bool blit_to_parent);

void
ui_group_draw_widget(t_ui_widget *widget, bool blit_to_parent);

#endif
