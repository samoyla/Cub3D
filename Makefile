# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/02 12:34:59 by masamoil          #+#    #+#              #
#    Updated: 2022/10/17 14:53:51 by iguscett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D

SRCS_DIR	=	srcs/

CSRCS		=	cub3d.c \
				check_map_file.c \
				init.c \
				utils.c \
				events.c \
				free.c \
				draw.c \
				get_map_info.c \
				map_elements.c \
				gnl.c \
				map_devision.c \
				control_variables.c \
				decor.c \
				map.c \
				check_wind_rose_n_colors.c \

SRCS		=	$(addprefix $(SRCS_DIR), $(CSRCS))

OBJS_DIR	=	objs/

OBJ			=	$(CSRCS:.c=.o)

OBJS		=	$(addprefix $(OBJS_DIR), $(OBJ))

DEPS_DIR	=	headers/

MLXLIB		=	./mlx/libmlx_Linux.a

LIBFT		=	./libft/libft.a

MLX			=	libmlx.dylib

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -g

FL_MLX		=	-ldl -lmlx -Lmlx -lm -lXext -lX11 -lz

MLXFLAGS	=	-I/usr/include -Imlx -O3

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@mkdir -p $(OBJS_DIR)
				@$(CC) -g $(MLXFLAGS) -I$(DEPS_DIR) -c -o $@ $<

all:			$(NAME)

mlxlib:
				@make -C ./mlx

$(NAME):		$(OBJS)
				@make -sC ./libft
				@make -sC ./mlx
				# @mv mlx/$(MLX) .
				@$(CC) -I$(DEPS_DIR) $(CFLAGS) -Imlx $(OBJS) $(LIBFT) -o $(NAME) $(FL_MLX)

clean:
				@$(RM) -r $(OBJS)
				@make clean -sC ./libft
				@make clean -sC ./mlx

fclean:			clean
				@make fclean -sC ./libft
				@make clean -sC ./mlx
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re








# all : ${NAME}

# ${NAME} : ${OBJS}
# 	make -C ./Libft
# 	make -s -C ./mlx
# 	${CC} ${CFLAGS} -Imlx ${SRCS} ${INCLUDES} -o ${NAME} ${FL_MLX}

# %.o:%.c
# 	${CC} ${CFLAGS} -Imlx -Ibass -o $@ -c $<

# clean :
# 	${RM} ${OBJS}
# 	make clean -C ./Libft

# fclean : clean
# 	${RM} ${NAME}
# 	make fclean -C ./Libft

# re : fclean all

# .PHONY : clean fclean re
