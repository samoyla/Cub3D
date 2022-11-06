/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:13:30 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:59:07 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hud_put_empty_square(t_data *data, int x, int y, int color)
{
	int ix;
	int iy;

	ix = x * data->hud.xt;
	while (ix < (x + 1) * data->hud.xt)
	{
		iy = y * data->hud.yt;
		while (iy < (y + 1) * data->hud.yt)
			img_pix_put(&data->img, ix, iy++, color);
		ix++;
	}
}

void walls_edges(t_data *data, int x, int y, int color)
{
	int ix;
	int iy;

	ix = x * data->hud.xt;
	iy = y * data->hud.yt;
	while (ix < (x + 1) * data->hud.xt)
	{
		img_pix_put(&data->img, ix, iy, color);
		img_pix_put(&data->img, ix, iy + 1, color);
		img_pix_put(&data->img, ix, iy + data->hud.yt - 1, color);
		img_pix_put(&data->img, ix, iy + data->hud.yt - 2, color);
		ix++;
	}
	ix = x * data->hud.xt;
	while (iy < (y + 1) * data->hud.yt)
	{
		img_pix_put(&data->img, ix, iy, color);
		img_pix_put(&data->img, ix + 1, iy, color);
		img_pix_put(&data->img, ix + data->hud.xt + 1, iy, color);
		img_pix_put(&data->img, ix + data->hud.xt, iy, color);
		img_pix_put(&data->img, ix + data->hud.xt - 1, iy, color);
		iy++;
	}
}

void empty_spaces(t_data *data)
{
	int y;
	int x;

	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == '0' || data->map.map[y][x] == 'N'
				|| data->map.map[y][x] == 'S' || data->map.map[y][x] == 'W'
				|| data->map.map[y][x] == 'E')
				hud_put_empty_square(data, x, y, GREY);
			else if (data->map.map[y][x] == '2' || data->map.map[y][x] == ' ')
				hud_put_empty_square(data, x, y, WHITE);
		}
	}
}

void black_edges(t_data *data)
{
	int y;
	int x;

	y = -1;
	while (data->map.map[++y])
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == '1')
				walls_edges(data, x, y, BLACK);
		}
	}
}

void render_hud(t_data *data, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->hud.ysize)
	{
		x = -1;
		while (++x < data->hud.xsize)
			img_pix_put(&data->img, x, y, color);
	}
	int k = -1;
	empty_spaces(data);
	black_edges(data);
}
