/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 22:35:57 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/21 18:15:08 by iguscett         ###   ########.fr       */
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
	// update_screen_points(data);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt, data->player.pos.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt+1, data->player.pos.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt, data->player.pos.y * data->hud.yt+1, STRONG_BLUE);
	img_pix_put(&data->img, data->player.pos.x * data->hud.xt+1, data->player.pos.y * data->hud.yt+1, STRONG_BLUE);

	img_pix_put(&data->img, data->player.screen.pleft.x * data->hud.xt, data->player.screen.pleft.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.screen.pleft.x * data->hud.xt+1, data->player.screen.pleft.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.screen.pleft.x * data->hud.xt, data->player.screen.pleft.y * data->hud.yt+1, STRONG_BLUE);
	img_pix_put(&data->img, data->player.screen.pleft.x * data->hud.xt+1, data->player.screen.pleft.y * data->hud.yt+1, STRONG_BLUE);


	img_pix_put(&data->img, data->player.screen.pright.x * data->hud.xt, data->player.screen.pright.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.screen.pright.x * data->hud.xt+1, data->player.screen.pright.y * data->hud.yt, STRONG_BLUE);
	img_pix_put(&data->img, data->player.screen.pright.x * data->hud.xt, data->player.screen.pright.y * data->hud.yt+1, STRONG_BLUE);
	img_pix_put(&data->img, data->player.screen.pright.x * data->hud.xt+1, data->player.screen.pright.y * data->hud.yt+1, STRONG_BLUE);


}
