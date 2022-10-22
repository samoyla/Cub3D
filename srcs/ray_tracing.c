/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:35:57 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/22 13:01:46 by iguscett         ###   ########.fr       */
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
	int i;

	i = -1;
	// printf("data->width:%d\n", data->width);
	while(++i < data->width)
	{
		// img_pix_put(&data->img, (data->screen.pleft.x  + data->screen.incr * data->screen.v.vx * i) * data->hud.xt, (data->screen.pleft.y + data->screen.incr * data->screen.v.vy * i) * data->hud.yt, STRONG_BLUE);
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
