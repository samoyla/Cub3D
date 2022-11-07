/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_update_positions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 16:18:09 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	screen_points_update(t_data *data)
{
	double	norm;

	data->screen.pleft.x = data->player.pos.x + data->half;
	data->screen.pleft.y = data->player.pos.y + DIST;
	data->screen.pright.x = data->player.pos.x - data->half;
	data->screen.pright.y = data->player.pos.y + DIST;
	z_rotation(data, &data->screen.pleft, data->player.angle);
	z_rotation(data, &data->screen.pright, data->player.angle);
	data->screen.v.vx = data->screen.pright.x - data->screen.pleft.x;
	data->screen.v.vy = data->screen.pright.y - data->screen.pleft.y;
	norm = sqrt((data->screen.v.vx * data->screen.v.vx)
			+ (data->screen.v.vy * data->screen.v.vy));
	data->screen.v.vx /= norm;
	data->screen.v.vy /= norm;
}

void	z_angle_rotation(t_data *data, int key)
{
	int	i;

	i = 0;
	while (i < NB_ANGLES && data->player.angle != data->player.angles[i])
		i++;
	if (key == XK_Left)
	{
		if (i == NB_ANGLES - 1)
			data->player.angle = data->player.angles[0];
		else
			data->player.angle = data->player.angles[++i];
	}
	else if (key == XK_Right)
	{
		if (i == 0)
			data->player.angle = data->player.angles[NB_ANGLES - 1];
		else
			data->player.angle = data->player.angles[--i];
	}
	data->player.v.vx = sin(data->player.angle);
	data->player.v.vy = cos(data->player.angle);
}

void	hud_points_update(t_data *data)
{
	data->hud.tri.p1.x_hud = data->player.posh.x + 0.25
		* sin(data->player.angle) * data->hud.xt;
	data->hud.tri.p1.y_hud = data->player.posh.y + 0.25
		* cos(data->player.angle) * data->hud.yt;
	data->hud.tri.p2.x_hud = data->player.posh.x + 0.16667
		* sin(PI * 0.25 - data->player.angle) * data->hud.xt;
	data->hud.tri.p2.y_hud = data->player.posh.y - 0.16667
		* cos(PI * 0.25 - data->player.angle) * data->hud.yt;
	data->hud.tri.p3.x_hud = data->player.posh.x - 0.16667
		* sin(PI * 0.25 + data->player.angle) * data->hud.xt;
	data->hud.tri.p3.y_hud = data->player.posh.y - 0.16667
		* cos(PI * 0.25 + data->player.angle) * data->hud.yt;
}

void	z_rotation_player(t_data *data, int key)
{
	z_angle_rotation(data, key);
	hud_points_update(data);
	screen_points_update(data);
}
