/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/09 13:04:43 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
//# include "Libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdint.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define FAILURE 1
# define SUCCESS 0

# define WIDTH 1200
# define HEIGHT 800
# define MLX_ERROR 1
# define PIXEL 0x07E0
# define BUFFER_SIZE 1

typedef struct s_map
{
	char	**whole;
	char	**map;
	char	**tx;
	int	ret;
	char 	**wind_rose;
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
}t_map;


typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}t_data;

//init.c
t_data	*init_data(t_data *data, char *name);
t_data	*init_image(t_data *data);
void	init_map(t_map *map);
//utils.c
void	ft_error(void);
void	ft_putstr_fd(char *s, int fd);
void	ft_exit(void);
void	print_tab(char	**tab);
void	free_tab(char **tab);
//events.c
int		handle_keypress(int keysem, t_data *data);
int		ft_red_cross(t_data *data);
//free.c
void	ft_free_n_destroy(t_data *data);
//draw.c
int		render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);
//parse.c
int		if_file_exists(char *pathname);
int		if_dir(char *pathname);
int		check_ext(char *name);
//gnl.c
char	*get_next_line(int fd);
//read_map.c
char	*s_n_r(char *str, char c, char ac);
void	tab_whole_map(char *pathname, t_map *map);
int		map_size(char *pathname);
//parse_map.c
void	tab_map(t_map *map, char *pathname);
//map_content.c
int		tab_texture(char *pathname, t_map *map);
//split.c
char	**ft_split(char	*s, char c);
//map_tx.c
void	get_tx(t_map *map);
#endif
