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

# include <stddef.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <time.h>
# include <string.h>
# include <errno.h>

# include "minilibx_mms_beta/mlx.h"
# include "libft/libft.h"
# include "libft/get_next_line.h"

# include "maths.h"
# include "image.h"
# include "keys.h"
# include "mouse.h"
# include "buffer.h"
# include "bmp.h"

# define WINDOW_NAME				"Cub3D"
# define WINDOW_NAME_BASE			"Cub3D - "

# define MAX_WINDOW_WIDTH			2560
# define MAX_WINDOW_HEIGHT			1440

# define CUB3D_FILE_EXTENSION		".cub"
# define CUB3D_USAGE				"usage: ./Cub3D <map> [-save]"

# define EXPORT_FILE				"Cub3D.bmp"

# define X_EVENT_KEY_PRESS			2
# define X_EVENT_KEY_RELEASE		3
# define X_EVENT_MOUSE_PRESS		4
# define X_EVENT_MOUSE_RELEASE		5
# define X_EVENT_MOUSE_MOVE			6
# define X_EVENT_EXIT				17

# define P_RESOLUTION				"R"
# define P_TEX_NORTH				"NO"
# define P_TEX_SOUTH				"SO"
# define P_TEX_WEST					"WE"
# define P_TEX_EAST					"EA"
# define P_SPRITE					"S"
# define P_FLOOR_COLOR				"F"
# define P_ROOF_COLOR				"C"

# define ORIENTATIONS				"NSEW"
# define NORTH						0
# define SOUTH						1
# define WEST						2
# define EAST						3

# define OBJ_EMPTY					0
# define OBJ_WALL					1
# define OBJ_SPRITE					2
# define OBJ_PLAYER					3

# define KEY_FORWARD				KEY_Z
# define KEY_FORWARD2				KEY_W
# define KEY_BACKWARD				KEY_S
# define KEY_LEFT					KEY_Q
# define KEY_LEFT2					KEY_A
# define KEY_RIGHT					KEY_D
# define KEY_ROTATION_LEFT			KEY_ARROW_LEFT
# define KEY_ROTATION_RIGHT			KEY_ARROW_RIGHT
# define KEY_MINIMAP				KEY_SPACE

# define MOUSE_BUTTON_HOOK			MOUSE_BUTTON_RIGHT
# define MOUSE_SENSIBILITY			2

# define MINIMAP_RES				16

# ifndef BONUS
#  define BONUS 1
# endif

# ifndef EXPERIMENTAL
#  define EXPERIMENTAL 0
# endif

# define RENDER_SHOW_STATS			BONUS
# define RENDER_DO_FRAMING			0

typedef struct		s_game_object
{
	int				type;
	t_vec2d			pos;
	int				flooded:1;
	void			*data;
}					t_game_object;

typedef struct		s_map
{
	char			*file;
	t_game_object	**objs;
	t_image			*wall_texs[4];
	t_image			*sprite;
	int				roof_color;
	int				floor_color;
	t_dim2i			size;
	t_game_object	**sprts;
	int				*spr_ordr;
	double			*spr_dist;
	size_t			sprite_count;
	int				render_minimap;
}					t_map;

typedef struct		s_mlx_context
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	int				graphics;
}					t_mlx_context;

typedef struct		s_player_speed
{
	double			base;
	double			boost_mult;
	double			value;
}					t_player_speed;

typedef struct		s_player
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
	double			sprint_mult;
	t_player_speed	move_speed;
	t_player_speed	rot_speed;
}					t_player;

typedef struct		s_engine
{
	t_mlx_context	ctx;
	char			*str;
	t_map			*map;
	t_player		player;
	t_image			*canvas;
	int				dirty;
	int				was_dirty;
}					t_engine;

typedef struct		s_ray_result
{
	int				height;
	int				start;
	int				end;
	int				obj_type;
}					t_ray_result;

typedef struct		s_ray_result_spr
{
	int				h;
	int				w;
	int				start_y;
	int				end_y;
	int				start_x;
	int				end_x;
}					t_ray_result_s;

typedef struct		s_ray
{
	int				x;
	t_engine		*engine;
	t_player		*player;
	t_vec2d			pos;
	int				width;
	int				h;
	t_vec2d			dir;
	t_vec2i			map;
	t_vec2d			step;
	t_vec2d			delta;
	double			perp_wall_dist;
	double			camera_x;
	t_vec2d			side_dist;
	int				side;
	int				hit;
	double			*zbuffer;
	t_vec2d			spr;
	double			inv_d;
	t_vec2d			trsnf;
	int				sprite_screen_x;
	int				v_mv_scrn;
	t_ray_result	out;
	t_ray_result_s	sout;
}					t_ray;

typedef struct		s_g_obj_data_player
{
	char			dir;
}					t_g_obj_data_player;

int					engine_initialize(char *path, int save_arg);
int					engine_loop(t_engine *engine);

int					engine_on_key_pressed(int keycode, t_engine *engine);
int					engine_on_key_released(int keycode, t_engine *engine);

int					engine_on_mouse_released(int button, int x, int y,
												t_engine *engine);
int					engine_on_mouse_pressed(int button, int x, int y,
												t_engine *engine);
int					engine_on_mouse_move(int x, int y, t_engine *engine);
int					engine_on_exit(t_engine *engine);

int					engine_handle_exit(t_engine *engine, int auto_exit);

void				*engine_error(char *error);
void				*engine_error_raison(char *error);

t_engine			*engine_global_set(t_engine *engine);
t_engine			*engine_global_get(void);
int					engine_global_is_set(void);

void				*mlx_context_initialize(t_mlx_context *context);
void				*mlx_window_initialize(t_engine *engine,
											t_mlx_context *context);
void				*mlx_canvas_initialize(t_engine *eng, t_image **canvas_ptr);

void				mlx_export_bmp(t_engine *engine);

int					color_assemble(int red, int green, int blue);
void				color_dismentle(int color, int *red, int *green, int *blue);

int					color_invert(int color);

t_map				*map_create(char *file);
t_map				*map_load(t_engine *eng, char *path);

int					map_loader_check_file_extension(char *path);
char				*map_loader_set_color(char *key, char *colors,
											int *color_ptr, char *name);
char				*map_loader_set_resolution(char *key, char **resolutions,
											t_engine *eng);
char				*map_loader_set_sprite_texture(t_engine *eng, t_map *map,
											char *path);
char				*map_loader_set_wall_texture(t_engine *eng, t_map *map,
											char *key, char *path);

char				*map_loader_grid_bind_object(t_map *map, size_t index,
										t_game_object *current, char c);
char				*map_loader_grid_create_line(t_game_object **grid,
												t_map *map, char *line);
char				*map_loader_parse_grid(t_engine *eng, t_map *map,
											char *line);

t_map				*map_finalize(t_map *map);

void				map_destroy(void *mlx_ptr, t_map **map_ptr);
void				map_destroy_textures(void *mlx_ptr, t_map *map);
void				map_destroy_grid(t_map *map);

int					map_sealing_check(t_map *map, t_vec2i start_pos);
char				*map_content_check(t_map *map);

int					map_is_empty_at(t_map *map, int x, int y);
int					map_is_solid_at(t_map *map, int x, int y);
int					map_is_sealing_at(t_map *map, int x, int y);

int					map_get_object_type_at(t_map *map, int x, int y);
t_game_object		*map_get_object_at(t_map *map, int x, int y);

void				map_dump_object(t_game_object object);
void				map_dump(t_map *map);

char				*map_side_to_str(int side);

char				*player_initialize(t_engine *engine);

char				*player_init_set_position(t_map *map,
														t_player *player);
char				*player_init_set_direction(t_player *player,
													t_g_obj_data_player *data);

int					player_handle_action(t_map *map, t_player *player);
int					player_handle_mouvement(t_map *map, t_player *player);

void				render_scene(t_engine *engine);
void				render_scene_smart(t_engine *engine, int show_stats);
void				render_display_fps(t_engine *engine);

void				ray_render_scene(t_engine *engine);

void				ray_compute_initialize_struct(t_ray *ray_ptr,
													t_engine *engine);
void				ray_compute(t_ray *ray_ptr);
void				ray_compute_initialize(t_ray *ray);
void				ray_compute_find_side(t_ray *ray);
void				ray_compute_dda(t_ray *ray);
void				ray_compute_distance(t_ray *ray);
void				ray_compute_set_limits(t_ray *ray);

void				ray_sprite_precomputer_order(t_player *player, t_map *map);
void				ray_sprite_compute(t_ray *r, t_game_object *spr);
void				ray_sprite_compute_matrix(t_ray *ray, t_game_object *spr);
void				ray_sprite_compute_set_limits(t_ray *ray);

void				ray_renderer_draw_default(t_engine *engine, t_ray *ray);

void				ray_renderer_draw_wall(t_engine *engine, t_ray *ray);
void				ray_renderer_wall_draw_texture(t_ray *ray, t_vec2i *tex_pos,
													t_image *tex);
t_image				*ray_renderer_wall_texture_finder(t_map *map, t_ray *ray);

void				ray_renderer_sprite_draw(t_engine *engine, t_ray *ray);
void				ray_renderer_sprite_draw_texture(t_ray *r, t_image *img,
													t_image *canvas);

void				fps_counter_end(void);
void				fps_counter_start(void);
int					fps_counter_get(void);
double				fps_counter_get_tick(void);

void				minimap_render(t_image *canvas, t_player *player,
									t_map *map);
void				minimap_render_outline(t_image *canvas, t_map *map,
											t_vec2i offset);
void				minimap_render_block(t_image *canvas, t_vec2i pos,
										int color, t_vec2i offset);
void				minimap_render_map(t_image *canvas, t_map *map,
										t_vec2i offset);
void				minimap_render_player(t_image *canvas, t_player *player,
											t_vec2i offset);

char				*e(const char *error);
char				*emalloc(const char *location);

#endif
