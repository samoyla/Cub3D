/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/16 12:51:47 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "./Libft/libft.h"
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

# define WIDTH 500
# define HEIGHT 300
# define MLX_ERROR 1
# define PIXEL 0x07E0
# define BUFFER_SIZE 1

typedef struct s_map
{
	char	**whole;
	char	**decor;
	char	**map;
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_red;
	int		c_green;
	int		c_blue;
}t_map;

typedef struct s_check
{
	int	c;
	int	f;
	int	no;
	int	so;
	int	we;
	int	ea;
}t_check;

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

//check_map_file.c
int		check_args(int ac);
int		check_file(char *s);
//init.c
void	init_map(t_map *map);
void	init_check(t_check *check);
t_data	*init_data(t_data *data, char *name);
t_data	*init_image(t_data *data);
//get_map_info.c
void	create_tab_elements(char *pathname, t_map *map);
char	*s_n_r(char *str, char c, char ac);
int		map_size(char *pathname);
void	tab_whole_map(char *pathname, t_map *map);
//map_elements.c
void	tab_map(char *pathname, t_map *map);
int		check_line_space(char *str);
void	tab_texture(char *pathname, t_map *map);
int		if_not_spaces(char *str);

//map_texture.c
int		get_texture(t_map *map);
//map_colors.c
void	get_color(t_map *map);

//control_variables.c
int		check_doubles(t_check *check);
//map_analysis.c
int		decor_analysis(t_map *map, t_check *check);
//check_wind_rose_and colors.c
int		check_windrose(t_check *check, char **split);
int		check_nb(char *str);
//utils.c
void	check_fd(int fd);
void	print_tab(char	**tab);
void	free_tab(char **tab);
int		if_str_digit(char *s);
int		digit_size(char *s);
//gnl.c
char	*get_next_line(int fd);
//MLX
//events.c
int		handle_keypress(int keysem, t_data *data);
int		ft_red_cross(t_data *data);
//free.c
void	ft_free_n_destroy(t_data *data);
//draw.c
int		render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);

#endif
