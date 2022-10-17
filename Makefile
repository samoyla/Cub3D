# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masamoil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/02 12:34:59 by masamoil          #+#    #+#              #
#    Updated: 2022/10/17 10:35:17 by masamoil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS	= cub3d.c\
	check_map_file.c\
 	init.c\
	utils.c\
	events.c\
	free.c\
	draw.c\
	get_map_info.c\
	map_elements.c\
	gnl.c\
	map_devision.c\
	decor.c\
	map.c\
	check_wind_rose_n_colors.c\
			
OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

INCLUDES = Libft/libft.a

CFLAGS = -Wall -Wextra -Werror -g

FL_MLX = -ldl -lmlx -Lmlx -lm -lXext -lX11 -lz

all : ${NAME}

${NAME} : ${OBJS}
	make -C ./Libft
	make -s -C ./mlx 
	${CC} ${CFLAGS} -Imlx ${SRCS} ${INCLUDES} -o ${NAME} ${FL_MLX}

%.o:%.c
	${CC} ${CFLAGS} -Imlx -Ibass -o $@ -c $<

clean :
	${RM} ${OBJS}
	make clean -C ./Libft
	
fclean : clean
	${RM} ${NAME}
	make fclean -C ./Libft
	
re : fclean all

.PHONY : clean fclean re
