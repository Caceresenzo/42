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

C_YELLOW_B=\033[1;33m
C_LIGHT_RED_B=\033[0;91m
C_WHITE=\033[0;97m
C_RESET=\033[0;39m

PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

NAME	=   Cub3D
SRCS	=	bmp_encoder.c \
			bmp_encoder_initializer.c \
			bmp_encoder_write_header.c \
			bmp_encoder_write_image_data.c \
			buffer_blit.c \
			buffer_create.c \
			buffer_destroy.c \
			buffer_fill.c \
			buffer_write_ascii.c \
			buffer_write_int_32_le.c \
			buffer_write_uint_16_le.c \
			buffer_write_uint_32_le.c \
			color_assemble.c \
			color_dismentle.c \
			color_invert.c \
			engine_exit_handler.c \
			engine_global.c \
			engine_handle_error.c \
			engine_initialization.c \
			engine_loop.c \
			engine_on_exit.c \
			engine_on_key_pressed.c \
			engine_on_key_released.c \
			engine_on_mouse_move.c \
			engine_on_mouse_pressed.c \
			engine_on_mouse_released.c \
			error_quick.c \
			fps_counter.c \
			image_clear.c \
			image_create.c \
			image_destroy.c \
			image_draw_line.c \
			image_load.c \
			image_pixel_get.c \
			image_pixel_set.c \
			image_value_ranger.c \
			keys_manager.c \
			keys_states.c \
			main.c \
			map_content_checker.c \
			map_destroy.c \
			map_dumper.c \
			map_loader.c \
			map_loader_create.c \
			map_loader_file_extension.c \
			map_loader_finalizer.c \
			map_loader_set_color.c \
			map_loader_set_grid.c \
			map_loader_set_resolution.c \
			map_loader_set_texture.c \
			map_side_to_str.c \
			map_sealing_checker.c \
			map_utils.c \
			minimap_renderer.c \
			minimap_renderer_block.c \
			minimap_renderer_map.c \
			minimap_renderer_outline.c \
			minimap_renderer_player.c \
			mlx_context_destroyer.c \
			mlx_context_initialization.c \
			mlx_exporter_bmp.c \
			mouse_buttons_states.c \
			mouse_positions.c \
			player_handle_action.c \
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
			renderer.c
			
OBJS	= $(SRCS:.c=.o)
CC		= cc
INCS	= -I. -Ilibft/ -Iminilibx_opengl/
FLAGS	= -O3 -g3 -Wall -Wextra -Werror
FRWRKS	= -framework OpenGL -framework AppKit
LIBS_P	= ${PROJECT_ROOT}/libmlx.dylib ${PROJECT_ROOT}/libft/libft.a

BONUS			= 0
EXPERIMENTAL	= 0

%.o: $(PROJECT_ROOT)%.c
	${CC} ${FLAGS} -c $(CPPFLAGS) -o $@ $< ${INCS} -D BONUS=${BONUS} -D EXPERIMENTAL=${EXPERIMENTAL}

$(NAME): ${OBJS}
	make libs -C ${PROJECT_ROOT}
	gcc $(OBJS) ${FLAGS} ${FRWRKS} -o $(NAME) ${LIBS_P}

all: $(NAME)

libs:
	make -C ${PROJECT_ROOT}/minilibx_mms_beta
	make -C ${PROJECT_ROOT}/libft
	cp ${PROJECT_ROOT}/minilibx_mms_beta/libmlx.dylib ./libmlx.dylib

clean:
	rm -fr cub3d $(OBJS)
	rm -rf .*.o
	rm -rf .*.dylib
    
fclean: clean
	$(RM) $(NAME)
    
re: fclean all

bonus:
	echo ${FILE}
	make re BONUS=1 -C ${PROJECT_ROOT}

libs-clean:
	make clean -C ${PROJECT_ROOT}/minilibx_mms_beta
	make fclean -C ${PROJECT_ROOT}/libft

norm:
	norminette *.[ch]

test: all
	sh ./tests/test_unit.sh

.PHONY: all bonus clean fclean re .c.o libs libs-clean norm test