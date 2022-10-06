# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: masamoil <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/02 12:34:59 by masamoil          #+#    #+#              #
#    Updated: 2022/10/06 16:26:02 by masamoil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

SRCS	= cub3d.c init.c utils.c events.c free.c draw.c parse.c\
	gnl.c read_map.c parse_map.c
			
OBJS = ${SRCS:.c=.o}

CC = clang

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

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
