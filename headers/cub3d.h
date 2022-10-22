/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/22 10:51:56 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"
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
# include <limits.h>

# define FAILURE 1
# define SUCCESS 0

# define WIDTH 500
# define HEIGHT 300
# define MLX_ERROR 1
# define PIXEL 0x07E0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# endif

typedef struct s_map
{
	char	**whole;
	char	**decor;
	char	**map;
	char	*input;
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
	int		size;
	int		count;
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

typedef struct s_read
{
	int		eof;
	ssize_t	b_read;
	int		fd;
	char	*temp;

}t_read;

//check_map_file.c
int		check_args(int ac);
int		check_file(char *s);
//init.c
void	init_map(t_map *map);
void	init_check(t_check *check);
void	get_map(t_map *map);
t_data	*init_data(t_data *data, char *name);
t_data	*init_image(t_data *data);
//read_input.c
void	read_input(t_map *map, char **argv);
//get_map_info.c
int		create_tab_elements(char *pathname, t_map *map, t_check *check, char **av);
char	*s_n_r(char *str, char c, char ac);
int		map_size(char *pathname);
void	tab_whole_map(t_map *map, char **av);
//map_elements.c
int		tab_map(char *pathname, t_map *map);
int		check_line_space(char *str);
void	tab_decor(char *pathname, t_map *map);
int		check_space(char *str);
//map_devision.c
void	get_texture(t_map *map);
void	get_color(t_map *map);
//decor.c
int		decor_analysis(t_map *map, t_check *check);
//check_wind_rose_and colors.c
int		check_doubles(t_check check);
int		check_exist(t_check check);
int		check_windrose(t_check *check, char **split);
int		check_nb(char *str);
//map.c
int		map_analysis(t_map *map);
//fill_map.c
int		max_width(char **map);
char	*ft_strdup_space(char *s, int size);
//utils.c
void	check_fd(int fd);
void	print_tab(char	**tab);
int		if_str_digit(char *s);
int		digit_size(char *s);
//gnl
char	*get_next_line(int fd);
//MLX
//events.c
int		handle_keypress(int keysem, t_data *data, t_map *map);
int		ft_red_cross(t_data *data, t_map *map);
//free.c
void	ft_free_n_destroy(t_data *data);
void	free_tab(char **tab);
void	free_map_struct(t_map *map);
//draw.c
int		render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);

#endif
