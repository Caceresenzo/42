/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 00:00:19 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/26 00:00:19 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "ui.h"

void
ui_application_dump(t_ui_application *app);

void
ui_window_dump(t_ui_window *window);

void
ui_widget_dump(t_ui_widget *widget);

#endif
