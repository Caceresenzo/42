/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:22:03 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/26 00:22:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CALLBACK_H
# define CALLBACK_H

void
ui_callback_size_call(t_ui_widget *widget);

void
ui_callback_draw_call(t_ui_widget *widget);

int
ui_callback_event_call(t_ui_widget *widget, const t_ui_event_base *event);

#endif
