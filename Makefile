# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masamoil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/02 12:34:59 by masamoil          #+#    #+#              #
#    Updated: 2022/10/13 12:24:40 by masamoil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS	= cub3d.c\
	check_map_file.c\
 	init.c\
	utils.c\
	events.c\
	free.c\
	draw.c\
	get_map_info.c\
	get_whole_map.c\
	map_elements.c\
	gnl.c\
	map_texture.c\
	map_colors.c\
	split.c\
	trim.c\
	control_variables.c\
	map_analysis.c\
	check_wind_rose.c	
			
OBJS = ${SRCS:.c=.o}

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g

FL_MLX = -ldl -lmlx -Lmlx -lm -lXext -lX11 -lz

all : ${NAME}

$(NAME) : $(OBJS)
	make -s -C ./mlx
	${CC} ${CFLAGS} -Imlx ${SRCS} -o ${NAME} $(FL_MLX)

%.o:%.c
	${CC} ${CFLAGS} -Imlx -Ibass -o $@ -c $<

clean :
	${RM} ${OBJS}
	
fclean : clean
	${RM} ${NAME}
	
re : fclean all

.PHONY : clean fclean re
