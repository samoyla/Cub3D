/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:13:30 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/18 18:55:31 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, int color)
{
	int	y;
	int	x;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			img_pix_put(img, x, y, color);
	}
}

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

double sign(t_data *data, double x, double y, t_pt pa, t_pt pb)
{
	double a;
	double b;

	a = (x - pb.x * data->hud.xt) * (pa.y * data->hud.yt - pb.y * data->hud.yt);
	b = (pa.x * data->hud.xt - pb.x * data->hud.xt) * (y - pb.y * data->hud.yt);
	return (a - b);
}

int is_in_triangle(t_data *data, double x, double y)
{
	double a;
	double b;
	double c;
	int has_neg;
	int has_pos;

	a = sign(data, x, y, data->hud.tri.p1 , data->hud.tri.p2);
	b = sign(data, x, y, data->hud.tri.p2, data->hud.tri.p3);
	c = sign(data, x, y, data->hud.tri.p3, data->hud.tri.p1);
	has_neg = 0;
	if ((a < 0) || (b < 0) || (c < 0))
		has_neg = 1;
	has_pos = 0;
	if ((a > 0) || (b > 0) || (c > 0))
		has_pos = 1;
	// printf("neg:%d pos:%d -> a:%f b:%f c:%f\n", has_neg, has_pos, a, b, c);
	if (has_neg && has_pos)
		return (0);
	return (1);
	// return !(has_neg && has_pos);
}

void render_player(t_data *data, int color)
{
	double x_init;
	double y_init;

	x_init = data->player.pos.x * data->hud.xt - 0.25 * data->hud.xt -1;

	// printf("Player x:%f y:%f\n", data->player.pos.x, data->player.pos.y);

	while (x_init <= data->player.pos.x * data->hud.xt + 0.25 * data->hud.xt)
	{
		y_init = data->player.pos.y * data->hud.yt - 0.25 * data->hud.yt -1;
		while (y_init <= data->player.pos.y * data->hud.yt + 0.25 * data->hud.yt)
		{
			if (is_in_triangle(data, x_init, y_init))
			img_pix_put(&data->img, x_init, y_init, color);
			y_init++;
		}
		x_init++;
	}

	// printf("isintri init:%d\n", is_in_triangle(data, x_init, y_init));
	// printf("isintri main:%d\n", is_in_triangle(data, data->player.pos.x * data->hud.xt, data->player.pos.y * data->hud.yt));



	// INIT
	// img_pix_put(&data->img, x_init, y_init, BLUE);

	// // MAIN
	// img_pix_put(&data->img, data->player.pos.x * data->hud.xt, data->player.pos.y * data->hud.yt, color);

	// // P1
	// img_pix_put(&data->img, data->hud.tri.p1.x * data->hud.xt, data->hud.tri.p1.y * data->hud.yt, color);

	// // P2
	// img_pix_put(&data->img, data->hud.tri.p2.x * data->hud.xt, data->hud.tri.p2.y * data->hud.yt, color);

	// // P3
	// img_pix_put(&data->img, data->hud.tri.p3.x * data->hud.xt, data->hud.tri.p3.y * data->hud.yt, color);
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE);
	render_hud(data, STRONG_BLUE);
	render_player(data, YELLOW);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	return (0);
}


