# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecaceres <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/13 15:11:33 by ecaceres          #+#    #+#              #
#    Updated: 2019/08/13 15:11:34 by ecaceres         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

NAME	=   cub3d
SRCS	=	bmp_encoder.c \
			bmp_encoder_initializer.c \
			bmp_encoder_write_header.c \
			bmp_encoder_write_image_data.c \
			buffer_blit.c \
			buffer_create.c \
			buffer_destroy.c \
			buffer_write_ascii.c \
			buffer_write_int_32_le.c \
			buffer_write_uint_16_le.c \
			buffer_write_uint_32_le.c \
			engine_exit_handler.c \
			engine_handle_error.c \
			engine_initialization.c \
			engine_loop.c \
			engine_on_exit.c \
			engine_on_key_pressed.c \
			engine_on_key_released.c \
			engine_on_mouse_move.c \
			engine_on_mouse_pressed.c \
			engine_on_mouse_released.c \
			fps_counter.c \
			image_clear.c \
			image_create.c \
			image_destroy.c \
			image_draw_line.c \
			image_load.c \
			keys_manager.c \
			keys_states.c \
			main.c \
			map_content_checker.c \
			map_destroy.c \
			map_dumper.c \
			map_loader.c \
			map_loader_finalizer.c \
			map_loader_set_color.c \
			map_loader_set_grid.c \
			map_loader_set_resolution.c \
			map_loader_set_texture.c \
			map_sealing_checker.c \
			map_utils.c \
			mlx_context_destroyer.c \
			mlx_context_initialization.c \
			mlx_exporter_bmp.c \
			player_handle_mouvement.c \
			player_initialization.c \
			player_initialization_set_direction.c \
			player_initialization_set_position.c \
			ray_computer.c \
			ray_computer_dda.c \
			ray_computer_distance.c \
			ray_computer_initialization.c \
			ray_computer_limiter.c \
			ray_computer_side_finder.c \
			ray_renderer.c \
			ray_renderer_default.c \
			ray_renderer_sprites.c \
			ray_renderer_walls.c \
			ray_sprite_computer.c \
			ray_sprite_computer_limiter.c \
			ray_sprite_computer_matrix.c \
			ray_sprite_precomputer_order.c \
			renderer.c \
			util_color.c
			
OBJS	= $(SRCS:.c=.o)
INCS	= -I. -Ilibft/ -Iminilibx_opengl/

.c.o :
	${CC} ${FLAGS} -c $< -o ${<:.c=.o} ${INCS}
	
%.o: $(PROJECT_ROOT)%.c
	gcc ${INCS} -c -O3 -g3 $(CPPFLAGS) -o $@ $< 

$(NAME): libs ${OBJS}
	gcc $(OBJS) -O3 -g3 -framework OpenGL -framework AppKit -o $(NAME) ${PROJECT_ROOT}/libmlx.dylib ${PROJECT_ROOT}/libft/libft.a

all: $(NAME)

libs:
	make -C ${PROJECT_ROOT}/minilibx_mms_beta
	make -C ${PROJECT_ROOT}/libft
	cp ${PROJECT_ROOT}/minilibx_mms_beta/libmlx.dylib ./libmlx.dylib

clean:
	rm -fr cub3d $(OBJS)
	rm -rf .*.o
	rm -rf .*.dylib

fullclean: clean
	make clean -C ${PROJECT_ROOT}/minilibx_mms_beta
	make clean -C ${PROJECT_ROOT}/libft