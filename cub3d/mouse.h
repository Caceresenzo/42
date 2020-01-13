/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:24:43 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 12:24:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_H
# define MOUSE_H

# define MOUSE_BUTTON_COUNT 5

# define MOUSE_BUTTON_LEFT 1
# define MOUSE_BUTTON_RIGHT 2
# define MOUSE_BUTTON_MIDDLE 3

# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 4

# define STATE_RELEASED 0
# define STATE_PRESSED 1

char	*mouse_button_get_str(int button);

void	mouse_button_state_initialize(void);

int		mouse_button_state_set(int button, int state);
int		mouse_button_state_get(int button);

int		mouse_button_last_get(void);

void	mouse_pos_last_click_update(int x, int y);
t_vec2i	mouse_pos_last_click_get(void);

void	mouse_pos_current_update(int x, int y);
t_vec2i	mouse_pos_current_get(void);

void	mouse_pos_update_last_to_current(void);

#endif
