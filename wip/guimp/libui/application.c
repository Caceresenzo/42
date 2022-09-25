/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 23:25:04 by ecaceres          #+#    #+#             */
/*   Updated: 2022/09/25 23:25:04 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "application.h"

t_ui_application*
ui_application_new(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Error: %s\n", SDL_GetError());
		abort();
	}
	return (calloc(sizeof(t_ui_application), 1));
}

void
ui_application_destroy(t_ui_application *app)
{
	while (app->windows.first)
		ui_window_destroy(app->windows.first->data);
	free(app);
}

t_ui_window*
ui_application_find_window(t_ui_application *app, uint32_t id)
{
	t_list_node *node;
	t_ui_window *window;

	node = app->windows.first;
	while (node)
	{
		window = node->data;
		if (id == SDL_GetWindowID(window->_window))
			return (window);
		node = node->next;
	}

	return (window);
}

void
ui_application_draw(t_ui_application *app)
{
	t_list_node *node;

	node = app->windows.first;
	while (node)
	{
		ui_window_draw(node->data);
		node = node->next;
	}
}
