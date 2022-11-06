/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:49:57 by iguscett         ###   ########.fr       */
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

# define STRONG_BLUE		0x00004D98
# define YELLOW				0xFFFF00
# define RED				0xFF0000
# define WHITE				0xFFFFFF
# define GREY				0x9C9C9C
# define BLACK				0x000000

# define PI					3.1415

# define FOV				66 * PI / 180
# define CUB_SIZE			1
# define STEP				0.1
# define NB_ANGLES			64
# define DIST				0.1
# define HALF				(tan(FOV * 0.5) * DIST)
# define MAX_PDIST			HALF / sin(FOV * 0.5)
# define HUD_SIZE_FACTOR	4
# define HUD_X_SIZE			11
# define HUD_Y_SIZE			6

typedef struct	s_read
{
	int		eof;
	ssize_t	b_read;
	int		fd;
	char	*temp;

}				t_read;

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
	char	*addr;
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
	t_img	ea;
	t_img	so;
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

typedef struct	s_hcalc
{
	t_posi	wall;
	t_posi	matrix;
	t_vect	vangle;
}				t_hcalc;

typedef struct	s_wall
{
	t_img	texture;
	double	wall_height;
	int		wall_height_px;
	int		low_limit_px;
	int		high_limit_px;
	double	column;
	double	*wheight;
	double	*col;
	char	*side;

}				t_wall;

typedef struct	s_hud
{
	int		xsize;
	int		ysize;
	int		xt;
	int		yt;
	t_tri	tri;
}				t_hud;

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
	t_screen screen;
	t_wall	wall;
	t_imgs	tex;
	t_hud	hud;
}				t_data;



// ****************************************************	//
// INITIALIZATION										//
// ****************************************************	//
void	init_pointers(t_data *data);
void 	init_map_and_check_struct(t_data *data, t_check *check);
void	check_nb_args_and_file(t_data *data, int argc, char **argv);
void	get_and_analyze_map(t_data *data, t_check *check, char *pathname, char **av);
void	read_input(t_data *data, char **argv);
void	get_map_tex_and_colors(t_data *data, char *pathname);
void	decor_analysis(t_data *data, t_check *check);
void	tab_map(t_data *data, char *pathname);
void	map_analysis(t_data *data);
void	get_map(t_data *data);
void	init_player(t_data *data);
void 	init_screen_and_hud(t_data *data);

void	update_ray_step(t_data *data, t_hcalc *st);
void	update_raypos_and_matrix_idx_x(t_data *data, t_hcalc *st);
void	update_raypos_and_matrix_idx_y(t_data *data, t_hcalc *st);
void	update_wall_value_and_idx_x(t_data *data, t_hcalc *st, int *wall, int i);
void	update_wall_value_and_idx_y(t_data *data, t_hcalc *st, int *wall, int i);

void	init_data_image_textures(t_data *data, char *name);

int		map_size(char *pathname);
//map_elements.c

int		check_line_space(char *str);

int		check_space(char *str);
//decor.c

//check_wind_rose_and colors.c
int		check_doubles(t_check check);
int		check_exist(t_check check);
int		check_windrose(t_check *check, char **split);
int		check_nb(char *str);

//fill_map.c
int		max_width(char **map);
char	*ft_strdup_space(char *s, int size);
// textture
void	init_textures(t_data *data);
// PLAYER


// HUD
void	set_hud(t_data *data);
void	hud_put_empty_square(t_data *data, int x, int y, int color);
void 	walls_edges(t_data *data, int x, int y, int color);
void	empty_spaces(t_data *data);
void 	black_edges(t_data *data);
void 	render_hud(t_data *data, int color);

//events
void	screen_points_update(t_data *data);
void	z_angle_rotation(t_data *data, int key);
void	hud_points_update(t_data *data);
void 	z_rotation_player(t_data *data, int key);
int 	is_move_valid(t_data *data, t_posi pcheck);

// Ray tracing
void	ray_tracing(t_data *data);
void 	z_rotation(t_data *data, t_posi *p, double angle);
void	get_wall_height(t_data *data);
double	wall_boundary(double coord, double dir);
int		encode_trgb(uint8_t transparency, uint8_t red, uint8_t green, uint8_t blue);
int		create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);

//utils.c
void	check_fd(int fd);
void	print_tab(char	**tab);
int		if_str_digit(char *s);
int		digit_size(char *s);
int		encode_rgb(uint8_t red, uint8_t green, uint8_t blue);
double	norm_vector(t_vect v);
double	norm_two_points(t_posi p1, t_posi p2);
double	absd(double a);


//MLX
//events.c
int		handle_keypress(int keysem, t_data *data);
int		ft_red_cross(t_data *data);
//free.c
void	ft_free_n_destroy(t_data *data);
void	free_map_struct(t_map *map);
//draw.c
int		render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_data *data, int color);

void	exit_and_free(t_data *data, char *err, int exit_code);
void	exit_free_destroy(t_data *data, char *err, int exit_code);
void 	free_pointers_map(t_data *data);
void 	free_pointers_wall(t_data *data);
void	free_double_ptr_char(char **str);

#endif
