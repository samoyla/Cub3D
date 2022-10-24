/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:35:57 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/24 16:46:37 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	ix = -1;
	while (++ix < data->width)
	{
		iy = -1;
		while(++iy < data->height)
		{
			if ((iy < data->height / 2) && (data->screen.fullh / 2) - iy * data->screen.yincr > data->screen.wheight[ix] / 2)
				img_pix_put(&data->img, ix, iy, RED);
			else if ((iy > data->height / 2) && ((iy - data->height / 2) * data->screen.yincr > data->screen.wheight[ix] / 2))
				img_pix_put(&data->img, ix, iy, data->map.floor);
			else
				img_pix_put(&data->img, ix, iy, STRONG_BLUE);
		}
	}














	img_pix_put(&data->img, data->player.pos.x * data->hud.xt, data->player.pos.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt+1, data->player.pos.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt, data->player.pos.y * data->hud.yt+1, STRONG_BLUE);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt+1, data->player.pos.y * data->hud.yt+1, STRONG_BLUE);

	img_pix_put(&data->img, data->screen.pleft.x * data->hud.xt, data->screen.pleft.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->screen.pleft.x * data->hud.xt+1, data->screen.pleft.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->screen.pleft.x * data->hud.xt, data->screen.pleft.y * data->hud.yt+1, STRONG_BLUE);
	img_pix_put(&data->img, data->screen.pleft.x * data->hud.xt+1, data->screen.pleft.y * data->hud.yt+1, STRONG_BLUE);


	img_pix_put(&data->img, data->screen.pright.x * data->hud.xt, data->screen.pright.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->screen.pright.x * data->hud.xt+1, data->screen.pright.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->screen.pright.x * data->hud.xt, data->screen.pright.y * data->hud.yt+1, STRONG_BLUE);
	img_pix_put(&data->img, data->screen.pright.x * data->hud.xt+1, data->screen.pright.y * data->hud.yt+1, STRONG_BLUE);

}
