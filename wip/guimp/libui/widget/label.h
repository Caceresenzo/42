/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:45:07 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:45:07 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WIDGET_LABEL_H
# define WIDGET_LABEL_H

# include "../ui.h"

typedef struct s_color
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} t_color;

typedef struct s_ui_label
{
	t_ui_widget super;
	char *text;
	t_color background_color;
} t_ui_label;

t_ui_label*
ui_label_new(const char *text);

void
ui_label_set_text(t_ui_label *label, const char *text);

void
ui_label_set_background_color(t_ui_label *label, t_color background_color);

void
ui_label_size(t_ui_label *label, void *data);

void
ui_label_draw(t_ui_label *label, void *data);

#endif
