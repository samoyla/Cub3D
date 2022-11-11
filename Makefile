# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/02 12:34:59 by masamoil          #+#    #+#              #
#    Updated: 2022/11/10 11:15:20 by iguscett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS_DIR	=	srcs/

CSRCS		=	main.c \
				init_pointers.c \
				init_map_and_check_struct.c \
				get_and_analyze_map.c \
				get_whole_map.c\
				map_elements.c \
				decor_analysis.c \
				decor_analysis_more.c \
				get_map.c \
				init_player.c \
				init_screen_and_hud.c \
				wall_height_1.c \
				wall_height_2.c \
				init_data_image_textures.c \
				check_map_file.c \
				events.c \
				events_update_positions.c \
				events_validate_move.c \
				draw.c \
				draw_hud.c \
				map.c \
				check_wind_rose_n_colors.c\
				fill_map.c\
				read_input.c\
				ray_tracing.c \
				utils.c \
				utils_math.c \
				exit_free_destroy.c \
				exit_free_more.c \

SRCS		=	$(addprefix $(SRCS_DIR), $(CSRCS))

OBJS_DIR	=	objs/

OBJ			=	$(CSRCS:.c=.o)

OBJS		=	$(addprefix $(OBJS_DIR), $(OBJ))

DEPS_DIR	=	headers/

MLXLIB		=	./mlx/libmlx_Linux.a

LIBFT		=	./libft/libft.a

MLX			=	libmlx.dylib

CC			=	clang

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

FL_MLX		=	-ldl -lmlx -Lmlx -lm -lXext -lX11 -lz

MLXFLAGS	=	-I/usr/include -Imlx -O3

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@mkdir -p $(OBJS_DIR)
				@$(CC) -g $(CFLAGS) $(MLXFLAGS) -I$(DEPS_DIR) -c -o $@ $<

all:			$(NAME)

mlxlib:
				@make -C ./mlx

$(NAME):		$(OBJS)
				@make -sC ./libft
				@make -sC ./mlx
				@$(CC) -I$(DEPS_DIR) $(CFLAGS) -Imlx $(OBJS) $(LIBFT) -o $(NAME) $(FL_MLX)

clean:
				rm -rf $(OBJS_DIR)
				@make clean -sC ./libft
				@make clean -sC ./mlx

fclean:			clean
				@make fclean -sC ./libft
				@make clean -sC ./mlx
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re