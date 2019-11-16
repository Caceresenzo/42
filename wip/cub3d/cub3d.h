/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:37:35 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 14:37:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>

# include "minilibx_mms_beta/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# include "maths.h"
# include "keys.h"

# define WINDOW_NAME				"Hello World"

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_MOUSE_PRESS		4
# define X_EVENT_MOUSE_RELEASE		5
# define X_EVENT_MOUSE_MOVE			6
# define X_EVENT_EXIT				17

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

# define P_RESOLUTION "R"
# define P_TEX_NORTH "NO"
# define P_TEX_SOUTH "SO"
# define P_TEX_WEST "WE"
# define P_TEX_EAST "EA"
# define P_SPRITE "S"
# define P_FLOOR_COLOR "F"
# define P_ROOF_COLOR "C"

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

# define OBJ_EMPTY 0
# define OBJ_WALL 1
# define OBJ_OBJ 2
# define OBJ_PLAYER 3

# define E(error) ft_strdup(error)

typedef struct		s_image
{
	void			*ptr;
	char			*pic;
	int				bpp;
	int				stride;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct		s_game_object
{
	int				type;
	void			*data;
}					t_game_object;

typedef struct		s_map
{
	char			*file;
	t_vec2i			resolution;
	t_game_object	**objs;
	t_image			*wall_texs[4];
	t_image			*sprite;
	int				roof_color;
	int				floor_color;
	t_dim2i			size;
}					t_map;

typedef struct		s_mlx_context
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
}					t_mlx_context;

typedef struct		s_engine
{
	t_mlx_context	ctx;
	char			*str;
	t_map			*map;
}					t_engine;

typedef struct		s_g_obj_data_player
{
	int				dir;
}					t_g_obj_data_player;

int					engine_initialize(char *path, int save_arg);
void				*engine_hooks(t_engine *engine);
int					engine_loop(t_engine *engine);

int					engine_on_key_pressed(int keycode, t_engine *engine);
int					engine_on_key_released(int keycode, t_engine *engine);

int					engine_on_mouse_released(int button, int x, int y,
												t_engine *engine);
int					engine_on_mouse_pressed(int button, int x, int y,
												t_engine *engine);
int					engine_on_mouse_move(int x, int y, t_engine *engine);
int					engine_on_exit(t_engine *engine);

void				*engine_handle_error(char *error);

void				*mlx_context_initialize(t_mlx_context *context);
void				*mlx_window_initialize(t_mlx_context *context);

char				*key_get_str(int keycode);

int					color_assemble(int red, int green, int blue);
void				color_dismentle(int color, int *red, int *green, int *blue);

t_map				*map_load(t_engine *eng, char *path);

char				*map_loader_set_color(char *key, char *colors,
											int *color_ptr);
char				*map_loader_set_resolution(char *key, char **resolutions,
											t_engine *eng);
char				*map_loader_set_sprite_texture(t_engine *eng, t_map *map,
											char *path);
char				*map_loader_set_wall_texture(t_engine *eng, t_map *map,
											char *key, char *path);

char				*map_loader_grid_bind_object(t_game_object *current,
												char *str);
char				*map_loader_grid_create_line(t_game_object **grid,
												t_map *map, char **split);
char				*map_loader_parse_grid(t_engine *eng, t_map *map,
											char **split);

t_image				*image_create(t_engine *eng, int width, int height);
t_image				*image_load(t_engine *eng, char *path);

#endif
