/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:28:06 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:28:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLICATION_H
# define APPLICATION_H

# include "ui.h"

t_ui_application*
ui_application_new(void);

void
ui_application_destroy(t_ui_application *app);

t_ui_window*
ui_application_find_window(t_ui_application *app, uint32_t id);

void
ui_application_draw(t_ui_application *app);

#endif
