/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:35:57 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/26 21:28:31 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	// {
		// printf("imgx:%f c:%d col:%f  ", image->x, c, col);
		// printf("imgy:%f r:%d AND row:%f\n", image->y, r, row);
		// printf("col:%d and row:%d color:%d\n", c, r, (int)image->iaddr[c + r * ((int)image->x)]);
	// }
#include "cub3d.h"

int	get_image_pixel_color(t_img *image, double col, double row)
{
	int c;
	int r;

	// printf("p:%p\n", &image);
	c = (int)((col) * image->x);
	r = (int)(image->y * row);
	// printf("col:%f\n", col);
	printf("c:%d row:%d\n", c, (int)row);
	return ((int)image->iaddr[c + r]); // * CUB_SIZE for parametrization
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
	data->wall.wall_height = data->wheight[ix];
	data->wall.wall_height_px = (int)(data->wall.wall_height / data->screen.yincr);
	data->wall.low_limit_px = (data->height - data->wall.wall_height_px) / 2;
	if (data->wall.low_limit_px < 0)
		data->wall.low_limit_px = 0;
	data->wall.high_limit_px = data->wall.low_limit_px + data->wall.wall_height_px;
	if (data->wall.high_limit_px > data->height)
		data->wall.high_limit_px = data->height;
	// printf("w_height_px:%d w_low_px:%d w_high_px:%d\n", (int)(data->wall.wall_height / data->screen.yincr), data->wall.low_limit_px, data->wall.high_limit_px);
}

void get_wall_texture(t_data *data, int ix)
{
	// printf("side:%c\n", data->side[ix]);
	// printf("no:%p ea:%p so:%p we:%p\n", &data->tex.no, &data->tex.ea, &data->tex.so, &data->tex.we);
	if (data->side[ix] == 'N')
		data->wall.texture = &data->tex.no;
	else if (data->side[ix] == 'E')
		data->wall.texture = &data->tex.ea;
	else if (data->side[ix] == 'S')
		data->wall.texture = &data->tex.so;
	else if (data->side[ix] == 'W')
		data->wall.texture = &data->tex.we;
	// printf("te:%p\n", data->wall.texture);
}

void get_wall_column(t_data *data, int ix)
{
	data->wall.column = data->col[ix];
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
		color = get_image_pixel_color(data->wall.texture, data->wall.column, (row - data->wall.low_limit_px) / data->wall.wall_height_px);
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
	// int	ix;
	// int iy;

	// ix = -1;
	// while (++ix < data->width)
	// {
	// 	iy = 0;
	// 	while(iy < data->height && (iy * data->screen.yincr < (data->screen.yfull - data->wheight[ix]) / 2))
	// 		img_pix_put(&data->img, ix, iy++, data->map.ceilling);
	// 	while (iy < data->height && (iy * data->screen.yincr > (data->screen.yfull - data->wheight[ix]) / 2)
	// 		&& (iy * data->screen.yincr < (data->screen.yfull + data->wheight[ix]) / 2))
	// 		img_pix_put(&data->img, ix, iy++, STRONG_BLUE);
	// 	while (iy < data->height)
	// 		img_pix_put(&data->img, ix, iy++, data->map.floor);
	// }
	textures(data);
}






































// 333333333333333333333333333333333333333333333333 OKKKK ~~~~~~~~~~~~~~~~~~~~~~~~~

// void ray_tracing(t_data *data)
// {
// 	int	ix;
// 	int iy;
// 	int color;
// 	int row;

// 	ix = -1;
// 	// printf("data->width:%d data->screen.xincr*width:%f data->screen.xfull:%f\n", data->width, data->screen.xincr * data->width, data->screen.xhalf * 2);
// 	// printf("dat height:%d data->screen.yincr*height:%f data->screen.yfull:%f\n", data->width, data->screen.yincr * data->height, data->screen.yfull);
// 	while (++ix < data->width)
// 	{
// 		iy = 0;
// 		while(iy < data->height && (iy * data->screen.yincr < (data->screen.yfull - data->wheight[ix]) / 2))
// 		{
// 			// printf("d:%f\n", data->screen.yincr * iy);
// 			img_pix_put(&data->img, ix, iy++, data->map.ceilling);
// 		}
// 		while (iy < data->height && (iy * data->screen.yincr >= (data->screen.yfull - data->wheight[ix]) / 2)
// 			&& (iy * data->screen.yincr < (data->screen.yfull + data->wheight[ix]) / 2))
// 		{
// 			// img_pix_put(&data->img, ix, iy, data->map.floor);
// 			row = (int)(data->tex.no.y * (iy * data->screen.yincr - (data->screen.yfull - data->wheight[ix]) / 2) / data->wheight[ix]);
// 			// printf("row:%d\n", row);
// 			color = get_image_pixel_color(&data->tex.no, data->col[ix], iy * data->screen.yincr - (data->screen.yfull - data->wheight[ix]) / 2, data->wheight[ix], ix);
// 			// color = STRONG_BLUE;
// 			// printf("d:%f (yf-wh/2):% f wheight:%f row:%f\n", data->screen.yincr * iy, (data->screen.yfull - data->wheight[ix]) / 2, data->wheight[ix], iy * data->screen.yincr - (data->screen.yfull - data->wheight[ix]) / 2);
// 			img_pix_put(&data->img, ix, iy++, color);
// 			// printf("x:%d\n", (int)(data->tex.no.x * data->col[ix]));
// 			if ((int)(data->tex.no.x * data->col[ix]) == 0)
// 				printf("x:%d y:%d color:%d ix:%d iy:%d\n", (int)(data->tex.no.x * data->col[ix]), row, color, ix, iy);
// 			// pixel_to_image(&data->img, ix, iy++, color);
// 		}
// 		while (iy < data->height)
// 		{
// 			// printf("d:%f\n", data->screen.yincr * iy);
// 			img_pix_put(&data->img, ix, iy++, data->map.floor);
// 		}
// 	}
// 	// printf("-------------------\n-------------------------\n");
// }














































// > (data->wheight[ix] + data->height * data->screen.yincr) / 2)
// }

	// ix = -1;
	// while (++ix < data->width)
	// {
	// 	iy = -1;
	// 	d = 0;
	// 	while(++iy < data->height)
	// 	{
	// 		d = iy * data->screen.yincr;
	// 		if ((iy < data->height / 2) && d < (data->screen.yfull - data->wheight[ix]) / 2)
	// 			img_pix_put(&data->img, ix, iy, data->map.ceilling);
	// 		else if ((iy > data->height / 2) && d > (data->wheight[ix] + data->height * data->screen.yincr) / 2)
	// 			img_pix_put(&data->img, ix, iy, data->map.floor);
	// 		else
	// 		{
	// 			color = get_image_pixel_color(&data->tex.no, data->col[ix], d - (data->screen.yfull - data->wheight[ix]) / 2);
	// 			color = STRONG_BLUE;
	// 			img_pix_put(&data->img, ix, iy, color);
	// 		}
	// 	}
	// }
