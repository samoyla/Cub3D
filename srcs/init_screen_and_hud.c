/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_screen_and_hud.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:11:32 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 17:12:54 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_width_height(t_data *data)
{
	int	height_backup;

	data->mlx_ptr_size = NULL;
	data->mlx_ptr_size = mlx_init();
	if (data->mlx_ptr_size == NULL)
		exit_free_destroy(data, "Problem with mlx initialization\n", FAILURE);
	mlx_get_screen_size(data->mlx_ptr_size, &data->width, &data->height);
	if (data->width < WIDTH || data->height < HEIGHT)
	{
		height_backup = data->height;
		while (data->height >= height_backup)
		{
			data->width = data->width * 3 / 4;
			data->height = data->width * HEIGHT / WIDTH;
		}
	}
	else
	{
		data->width = WIDTH;
		data->height = HEIGHT;
	}
	mlx_destroy_display(data->mlx_ptr_size);
	free(data->mlx_ptr_size);
	data->mlx_ptr_size = NULL;
}

void	set_screen_lr_points(t_data *data)
{
	data->screen.pleft.x = data->player.pos.x + data->half;
	data->screen.pleft.y = data->player.pos.y + DIST;
	data->screen.pright.x = data->player.pos.x - data->half;
	data->screen.pright.y = data->player.pos.y + DIST;
	z_rotation(data, &data->screen.pleft, data->player.angle);
	z_rotation(data, &data->screen.pright, data->player.angle);
}

void	set_triangle(t_data *data)
{
	data->hud.tri.p1.x_map = data->player.pos.x
		+ 0.25 * sin(data->player.angle);
	data->hud.tri.p1.y_map = data->player.pos.y
		+ 0.25 * cos(data->player.angle);
	data->hud.tri.p2.x_map = data->player.pos.x
		+ 0.16667 * sin(PI * 0.25 - data->player.angle);
	data->hud.tri.p2.y_map = data->player.pos.y
		- 0.16667 * cos(PI * 0.25 - data->player.angle);
	data->hud.tri.p3.x_map = data->player.pos.x
		- 0.16667 * sin(PI * 0.25 + data->player.angle);
	data->hud.tri.p3.y_map = data->player.pos.y
		- 0.16667 * cos(PI * 0.25 + data->player.angle);
	data->hud.tri.p1.x_hud = data->hud.tri.p1.x_map * data->hud.xt;
	data->hud.tri.p1.y_hud = data->hud.tri.p1.y_map * data->hud.yt;
	data->hud.tri.p2.x_hud = data->hud.tri.p2.x_map * data->hud.xt;
	data->hud.tri.p2.y_hud = data->hud.tri.p2.y_map * data->hud.yt;
	data->hud.tri.p3.x_hud = data->hud.tri.p3.x_map * data->hud.xt;
	data->hud.tri.p3.y_hud = data->hud.tri.p3.y_map * data->hud.yt;
}

void	set_hud(t_data *data)
{
	if (data->map.xsize * data->height > data->map.ysize * data->width)
	{
		data->hud.xsize = data->width / HUD_SIZE_FACTOR;
		data->hud.ysize = data->hud.xsize * data->map.ysize / data->map.xsize;
	}
	else
	{
		data->hud.ysize = data->height / HUD_SIZE_FACTOR;
		data->hud.xsize = data->hud.ysize * data->map.xsize / data->map.ysize;
	}
	data->hud.xt = data->hud.xsize / data->map.xsize;
	data->hud.yt = data->hud.ysize / data->map.ysize;
	set_triangle(data);
	data->player.posh.x = data->player.pos.x * data->hud.xt;
	data->player.posh.y = data->player.pos.y * data->hud.yt;
}

void	init_screen_and_hud(t_data *data)
{
	double	norm;

	resize_width_height(data);
	set_screen_lr_points(data);
	data->screen.xincr = (data->half * 2) / data->width;
	data->screen.xfull = data->half * 2;
	data->screen.xhalf = data->half;
	data->screen.yfull = data->screen.xincr * data->height;
	data->screen.yincr = data->screen.yfull / data->height;
	data->screen.v.vx = (data->screen.pright.x - data->screen.pleft.x);
	data->screen.v.vy = (data->screen.pright.y - data->screen.pleft.y);
	norm = sqrt((data->screen.v.vx * data->screen.v.vx)
			+ (data->screen.v.vy * data->screen.v.vy));
	data->screen.v.vx /= norm;
	data->screen.v.vy /= norm;
	data->wall.wheight = malloc(sizeof(data->wall.wheight) * data->width);
	data->wall.col = malloc(sizeof(data->wall.col) * data->width);
	data->wall.side = malloc(sizeof(data->wall.side) * data->width);
	if (!data->wall.wheight || !data->wall.col || !data->wall.side)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	set_hud(data);
}
