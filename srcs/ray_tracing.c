/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:35:57 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/25 19:20:52 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_image_pixel_color(t_img *image, double col, double row)
{
	int c;
	int r;

	c = (int)(col * image->x);
	r = (int)(row * image->y);
	printf("imgx:%f c:%d imgy:%f r:%d\n", image->x, c, image->y, r);
	return ((int)image->addr[r + c]); // * CUB_SIZE for parametrization
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

void ray_tracing(t_data *data)
{
	int	ix;
	int iy;
	int color;
	double d;
	int	tx;
	int	ty;

	ix = -1;
	// printf("yincr:%f fullh:%f\n", data->screen.yincr, data->wheight[0] * data->screen.yincr);
	while (++ix < data->width)
	{
		iy = 0;
		d = 0;
		while(iy < data->height && (iy * data->screen.yincr < (data->screen.fullh - data->wheight[ix]) / 2))
			img_pix_put(&data->img, ix, iy++, data->map.ceilling);
		while (iy < data->height && (iy * data->screen.yincr > (data->screen.fullh - data->wheight[ix]) / 2)
			&& (iy * data->screen.yincr < (data->screen.fullh + data->wheight[ix]) / 2))
		{
			// img_pix_put(&data->img, ix, iy, data->map.floor);
			// color = get_image_pixel_color(&data->tex.no, data->col[ix], d - (data->screen.fullh - data->wheight[ix]) / 2);
			color = STRONG_BLUE;
			img_pix_put(&data->img, ix, iy++, color);
		}
		while (iy < data->height)
				img_pix_put(&data->img, ix, iy++, data->map.floor);
	}
}


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
	// 		if ((iy < data->height / 2) && d < (data->screen.fullh - data->wheight[ix]) / 2)
	// 			img_pix_put(&data->img, ix, iy, data->map.ceilling);
	// 		else if ((iy > data->height / 2) && d > (data->wheight[ix] + data->height * data->screen.yincr) / 2)
	// 			img_pix_put(&data->img, ix, iy, data->map.floor);
	// 		else
	// 		{
	// 			color = get_image_pixel_color(&data->tex.no, data->col[ix], d - (data->screen.fullh - data->wheight[ix]) / 2);
	// 			color = STRONG_BLUE;
	// 			img_pix_put(&data->img, ix, iy, color);
	// 		}
	// 	}
	// }
