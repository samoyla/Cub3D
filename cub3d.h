/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/05 18:21:09 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
#define _CUB3D_H_

# include "mlx/mlx.h"
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

#define FAILURE 1
#define SUCCESS 0

#define WIDTH 1200
#define	HEIGHT 800
#define MLX_ERROR 1
#define PIXEL 0x07E0
#define BUFFER_SIZE 1
typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int	bpp;
	int	line_len;
	int	endian;
}t_img;

typedef struct	s_data 
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}t_data;

//init.c
t_data	*init_data(t_data *data, char *name);
t_data	*init_image(t_data *data);
//utils.c
void	ft_error(void);
void	ft_putstr_fd(char *s, int fd);
void	ft_exit(void);
//events.c
int	handle_keypress(int keysem, t_data *data);
int	ft_red_cross(t_data *data);
//free.c
void	ft_free_n_destroy(t_data *data);
//draw.c
int	render(t_data *data);
void	img_pix_put(t_img *img, int x, int y, int color);
void	render_background(t_img *img, int color);
//parse.c
int	if_file_exists(char *pathname);
int	if_dir(char *pathname);
int	check_ext(char *name);
//gnl.c
char *get_next_line(int fd);

#endif
