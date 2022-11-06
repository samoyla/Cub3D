/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:35:57 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 15:54:00 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_image_pixel_color(t_img *image, double col, double row)
{
	int c;
	int r;

	c = (int)((col) * image->x);
	r = (int)(row * image->y);
	return ((int)image->iaddr[c + (int)(r * image->x)]);
}

void z_rotation(t_data *data, t_posi *p, double angle)
{
	double x;
	double y;

	x = p->x - data->player.pos.x;
	y = p->y - data->player.pos.y;
	p->y = data->player.pos.y + y * cos(angle) - x * sin(angle);
	p->x = data->player.pos.x + y * sin(angle) + x * cos(angle);
}

void get_wall_height_texture(t_data *data, int ix)
{
	data->wall.wall_height = data->wall.wheight[ix];
	data->wall.wall_height_px = (int)(data->wall.wall_height / data->screen.yincr);
	data->wall.low_limit_px = (data->height - data->wall.wall_height_px) / 2;
	data->wall.high_limit_px = data->wall.low_limit_px + data->wall.wall_height_px;
	if (data->wall.high_limit_px > data->height)
		data->wall.high_limit_px = data->height;
}

void get_wall_texture(t_data *data, int ix)
{
	if (data->wall.side[ix] == 'N')
		data->wall.texture = data->tex.no;
	else if (data->wall.side[ix] == 'E')
		data->wall.texture = data->tex.ea;
	else if (data->wall.side[ix] == 'S')
		data->wall.texture = data->tex.so;
	else if (data->wall.side[ix] == 'W')
		data->wall.texture = data->tex.we;
}

void get_wall_column(t_data *data, int ix)
{
	data->wall.column = data->wall.col[ix];
}

void texture_colums(t_data *data, int ix)
{
	int row;
	int color;

	get_wall_height_texture(data, ix);
	get_wall_texture(data, ix);
	get_wall_column(data, ix);
	row = 0;
	while (row < data->wall.low_limit_px)
		img_pix_put(&data->img, ix, row++, data->map.ceilling);
	while (row < data->wall.high_limit_px)
	{
		color = get_image_pixel_color(&data->wall.texture, data->wall.column, (double)(row - data->wall.low_limit_px) / data->wall.wall_height_px);
		img_pix_put(&data->img, ix, row++, color);
	}
	while (row < data->height)
		img_pix_put(&data->img, ix, row++, data->map.floor);
}

void textures(t_data *data)
{
	int	ix;

	ix = -1;
	while (++ix < data->width)
		texture_colums(data, ix);
}


void ray_tracing(t_data *data)
{
	textures(data);
}
