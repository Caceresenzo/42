/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:14:01 by ecaceres          #+#    #+#             */
/*   Updated: 2022/10/01 22:14:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"

void
ui_style_apply_size(t_ui_widget *widget)
{
	t_style *style = &widget->style;

	if (style->width.present)
		widget->size.x = style->width.value;
	if (style->min_width.present)
		widget->size.x = MAX(widget->size.x, style->min_width.value);
	if (style->max_width.present)
		widget->size.x = MIN(widget->size.x, style->max_width.value);

	if (style->height.present)
		widget->size.y = style->height.value;
	if (style->min_height.present)
		widget->size.y = MAX(widget->size.y, style->min_height.value);
	if (style->max_height.present)
		widget->size.y = MIN(widget->size.y, style->max_height.value);
}
