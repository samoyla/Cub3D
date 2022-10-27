/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/27 16:25:04 by iguscett         ###   ########.fr       */
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

# define FAILURE			1
# define SUCCESS			0

# define WIDTH				1280
# define HEIGHT				720
# define SCALING_FACTOR		1000
# define SCALE				64
# define MLX_ERROR 			1
# define BUFFER_SIZE		1
# define HUD_SIZE_FACTOR	4

# define PI					3.1415
# define FOV				66 * PI / 180

# define BLUE				0x07E0
# define STRONG_BLUE		0x004D98
# define YELLOW				0xFFFF00
# define RED				0xFF0000
# define WHITE				0xFFFFFF
# define GREY				0x9C9C9C
# define BLACK				0x000000

// Events
# define CUB_SIZE			1
# define STEP				0.05 //* SCALE //0.2 * SCALING_FACTOR
# define NB_ANGLES			64
# define ROT				PI * 0.125
static double angles[17] = {0, PI * 0.125, PI * 0.25, PI * 0.375, PI * 0.5, PI * 0.625, PI * 0.75, PI * 0.875,
							PI, PI * 1.125, PI * 1.25, PI * 1.375, PI * 1.5, PI * 1.625, PI * 1.75, PI * 1.875, -1};

// Raycasting
# define DIST				0.1 //* SCALE //0.1 * SCALING_FACTOR
# define HALF				(tan(FOV * 0.5) * DIST) //* SCALE //* SCALING_FACTOR
# define MAX_PDIST			HALF / sin(FOV * 0.5)

typedef struct	s_map
{
	char	**whole;
	char	**decor;
	char	**map;
	char	*input;
	char	*so;
	char	*no;
	char	*ea;
	char	*we;
	long int	xsize;
	long int	ysize;
	int		size;
	int		count;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		c_red;
	int		c_green;
	int		c_blue;
	int			floor;
	int			ceilling;
}				t_map;

typedef struct s_check
{
	int	c;
	int	f;
	int	no;
	int	so;
	int	we;
	int	ea;
}t_check;

typedef struct	s_img
{
	void	*img;
	char	*addr; // passer en int*?
	int		*iaddr;
	int		bpp;
	int		line_len;
	int		endian;
	double	x;
	double	y;
}				t_img;

typedef struct	s_imgs
{
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
}				t_imgs;

typedef struct	s_posi
{
	double	x;
	double	y;
	double	z;
}				t_posi;

typedef struct	s_vect
{
	double	vx;
	double	vy;
}				t_vect;

typedef struct	s_screen
{
	double	xfull;
	double	xhalf;
	double	xincr;
	double	yfull;
	double	yincr;
	double	point_angle;
	t_posi	pleft;
	t_posi	pright;
	t_vect	v;

}				t_screen;

typedef struct	s_playr
{
	t_posi	pos;
	t_posi	posh;
	double	angle;
	double	*angles;
	t_vect	v;
	t_posi	check;
	t_posi	rayp;
	t_posi	matpos;
	t_posi	wall;
	t_posi	dist;
	t_posi	step;
}				t_playr;

typedef struct	s_hpt
{
	double	x_map;
	double	y_map;
	double	x_hud;
	double	y_hud;
}				t_hpt;

typedef struct	s_tri
{
	t_hpt	p1;
	t_hpt	p2;
	t_hpt	p3;
}				t_tri;

typedef struct	s_hud
{
	int		xsize;
	int		ysize;
	int		xt;
	int		yt;
	t_tri	tri;
}				t_hud;

typedef struct	s_wall
{
	t_img	*texture;
	double	wall_height;
	int		wall_height_px;
	int		low_limit_px;
	int		high_limit_px;
	double	column;

}				t_wall;

typedef struct	s_data
{
	void	*mlx_ptr_size;
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	t_map	map;
	t_img	img;
	t_playr	player;
	t_hud	hud;
	t_screen screen;
	t_wall	wall;
	t_imgs	tex;
	// double	*dist;
	double	*wheight;
	double	*col;
	char	*side;
	int		*wallnb;


}				t_data;

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
// textture
void	init_textures(t_data *data);
//resize_width_height.c
void	resize_width_height(t_data *data);
//map_size.c
void		get_map_size(t_map *map);
// PLAYER
void	init_player(t_data *data);

// HUD
void	set_hud(t_data *data);

// SCREEN LINE
void 	init_screen(t_data *data);;

// Ray tracing
void	ray_tracing(t_data *data);
void 	z_rotation(t_data *data, t_posi *p, double angle);
void	get_wall_height(t_data *data);
double	wall_boundary(double coord, double dir);

//utils.c
void	check_fd(int fd);
void	print_tab(char	**tab);
int		if_str_digit(char *s);
int		digit_size(char *s);
double	absd(double a);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);

//MLX
//events.c
int		handle_keypress(int keysem, t_data *data);
int		ft_red_cross(t_data *data);
//free.c
void	ft_free_n_destroy(t_data *data);
void	free_tab(char **tab);
void	free_map_struct(t_map *map);
//draw.c
int		render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_data *data, int color);

#endif
