/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:32:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:32:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_CONTAINER_H
# define WIDGET_CONTAINER_H

#include "../ui.h"

typedef enum e_ui_container_direction
{
	CONTAINER_DIRECTION_VERTICAL,
	CONTAINER_DIRECTION_HORIZONTAL,
} t_ui_container_direction;

typedef struct s_ui_container
{
	t_ui_widget super;
	t_ui_container_direction direction;
} t_ui_container;

t_ui_container*
ui_container_new(t_ui_container_direction direction);

void
ui_container_size(t_ui_container *widget, void *data);

void
ui_container_draw(t_ui_container *widget, void *data);

#endif
