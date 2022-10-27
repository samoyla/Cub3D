/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:13:30 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/27 12:22:06 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8; // bpp = 32
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

void	render_background(t_data *data, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			img_pix_put(&data->img, x, y, color);
			x++;
		}
		y++;
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
		// printf("hudxsize:%d\n", data->hud.xsize);
		while (++x < data->hud.xsize)
			img_pix_put(&data->img, x, y, color);
	}
	int k = -1;
	empty_spaces(data);
	black_edges(data);
}

double sign(t_data *data, double x, double y, t_hpt pa, t_hpt pb)
{
	double a;
	double b;

	a = (x - pb.x_hud) * (pa.y_hud - pb.y_hud);
	b = (pa.x_hud - pb.x_hud) * (y - pb.y_hud);
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
	if (has_neg && has_pos)
		return (0);
	return (1);
}

void render_player(t_data *data, int color)
{
	double x_init;
	double y_init;

	x_init = data->player.pos.x * data->hud.xt - 0.25 * data->hud.xt -1;
	y_init = data->player.pos.y * data->hud.yt - 0.25 * data->hud.yt -1;
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
}

void px_to_image_debug(t_img *image, int x, int y, int color)
{
	image->addr[y + x] = color;
}

int	get_image_pixel_debug(t_img *image, int col, int row, int width)
{

	return ((int)image->iaddr[col + row * width]);
}

void render_image(t_data *data)
{
	// int color;
	// printf("RED int:%d\n", (int)GREY);
	// img_pix_put(&data->img, 476, 156, RED);
	// color = get_image_pixel_debug(&data->img, 476, 156, data->width);
	// printf("color int:%d\n", color);

	int i;
	int j;
	int xshift = 500;
	int yshift = 200; // starts here!
	int color;

	i = -1;
	while (++i < data->width)
	{
		j = -1;
		while (++j < data->height)
		{
			if (i < data->tex.no.x)
			{
				if (j < data->tex.no.y)
				{
					color = get_image_pixel_debug(&data->tex.no, i, j, (int)data->tex.no.x);
					// printf("i:%d and j:%d color:%d\n", i, j, color);
					img_pix_put(&data->img, i + xshift, j + yshift, color);
					// if (i == 0)
						printf("x:%d y:%d color:%d ix:%i iy:%d\n", i, j, color,i + xshift,j +yshift);
				}
			}
		}
	}
}

void print_col_row(t_data *data)
{
	int i = -1;
	int j = -1;
	int color;

	while (++i < data->tex.no.x)
	{
		j = -1;
		while (++j < data->tex.no.y)
		{
			color = get_image_pixel_debug(&data->tex.no, i, j, (int)data->tex.no.y);
			// printf("col:%d and row:%d color:%d\n", i, j, color);
			img_pix_put(&data->img, i, j, color);
		}
	}
}


int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);


	// // Ray tracing
	ray_tracing(data);


	// print_col_row(data);
	// render_image(data);

	render_hud(data, STRONG_BLUE);
	render_player(data, YELLOW);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	return (0);
}

















	// render_background(data, WHITE); // a supprimer car inutile

	// // render_background(data, WHITE); // a supprimer car inutile






	// img_pix_put(&data->img, data->player.check.x * data->hud.xt, data->player.check.y * data->hud.yt, STRONG_BLUE); // point checker

	// img_pix_put(&data->img, 1.047049 * data->hud.xt, 4.0 * data->hud.yt, RED); // bug wall
	// img_pix_put(&data->img, 1.999189 * data->hud.xt, 4.0 * data->hud.yt, RED); // bug wall

	// int i = - 1;
	// double j;
	// while (++i < data->map.xsize)
	// {
	// 	j = 0;
	// 	while (j < data->map.ysize)
	// 	{
	// 		img_pix_put(&data->img, i * data->hud.xt, j * data->hud.yt, RED); // bug wall
	// 		j += 0.05;
	// 	}
	// }
	// i = -1;
	// while (++i < data->map.ysize)
	// {
	// 	j = 0;
	// 	while (j < data->map.xsize)
	// 	{
	// 		img_pix_put(&data->img, j * data->hud.xt, i * data->hud.yt, RED); // bug wall
	// 		j += 0.05;
	// 	}
	// }

	// t_posi p;
	// p.x = data->screen.pleft.x  + data->screen.xincr * data->screen.v.vx * i;
	// p.y = data->screen.pleft.y + data->screen.xincr * data->screen.v.vy * i;
	// j = -1;
	// while (++j < 1000)
	// {
	// 	if (p.x * data->hud.xt > 0 && p.x * data->hud.xt < data->width
	// 		&& p.y * data->hud.yt > 0 && p.y * data->hud.yt < data->height)
	// 		img_pix_put(&data->img, p.x * data->hud.xt, p.y * data->hud.yt, RED); // bug wall
	// 	p.x += data->screen.xincr * data->player.v.vx * j;
	// 	p.y += data->screen.xincr * data->player.v.vy * j;
	// 	j += 0.05;
	// }
