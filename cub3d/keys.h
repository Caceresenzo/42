/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 12:24:43 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 12:24:43 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define KEY_COUNT 300

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6

# define KEY_0 29
# define KEY_1 18
# define KEY_2 19
# define KEY_3 20
# define KEY_4 21
# define KEY_5 23
# define KEY_6 22
# define KEY_7 26
# define KEY_8 28
# define KEY_9 25
# define KEY_DELETE 51
# define KEY_MINUS 27
# define KEY_PLUS 24

# define KEY_TAB 48
# define KEY_CAPS_LOCK 272
# define KEY_SHIFT 257
# define KEY_CONTROL 256
# define KEY_OPTION 261
# define KEY_COMMAND 259

# define KEY_ARROW_LEFT 123
# define KEY_ARROW_UP 126
# define KEY_ARROW_RIGHT 124
# define KEY_ARROW_DOWN 125

# define KEY_SPACE 49
# define KEY_ESCAPE 53

# define KEY_NUMPAD_0 82
# define KEY_NUMPAD_1 83
# define KEY_NUMPAD_2 84
# define KEY_NUMPAD_3 85
# define KEY_NUMPAD_4 86
# define KEY_NUMPAD_5 87
# define KEY_NUMPAD_6 88
# define KEY_NUMPAD_7 89
# define KEY_NUMPAD_8 91
# define KEY_NUMPAD_9 92
# define KEY_NUMPAD_DOT 65
# define KEY_NUMPAD_ENTER 76
# define KEY_NUMPAD_PLUS 69
# define KEY_NUMPAD_MINUS 78
# define KEY_NUMPAD_MULTIPLY 67
# define KEY_NUMPAD_DEVISE 75
# define KEY_NUMPAD_EQUAL 81
# define KEY_NUMPAD_CLEAR 71

# define KEY_FUNCTION 264
# define KEY_F1 122
# define KEY_F2 120
# define KEY_F3 99
# define KEY_F4 118
# define KEY_F5 96
# define KEY_F6 97
# define KEY_F7 98
# define KEY_F8 100
# define KEY_F9 101
# define KEY_F10 109
# define KEY_F11 110
# define KEY_F12 111

# define STATE_RELEASED 0
# define STATE_PRESSED 1

char	*key_get_str(int keycode);

void	key_state_initialize(void);

int		key_state_set(int keycode, int state);
int		key_state_get(int keycode);
int		key_state_get2(int keycode1, int keycode2);

#endif
