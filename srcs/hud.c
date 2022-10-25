/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:28:33 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/25 16:26:25 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_triangle(t_data *data)
{
	data->hud.tri.p1.x_map = data->player.pos.x + 0.25 * sin(data->player.angle);
	data->hud.tri.p1.y_map = data->player.pos.y + 0.25 * cos(data->player.angle);
	data->hud.tri.p2.x_map = data->player.pos.x + 0.16667 * sin(PI * 0.25 - data->player.angle);
	data->hud.tri.p2.y_map = data->player.pos.y - 0.16667 * cos(PI * 0.25 - data->player.angle);
	data->hud.tri.p3.x_map = data->player.pos.x - 0.16667 * sin(PI * 0.25 + data->player.angle);
	data->hud.tri.p3.y_map = data->player.pos.y - 0.16667 * cos(PI * 0.25 + data->player.angle);
	data->hud.tri.p1.x_hud = data->hud.tri.p1.x_map * data->hud.xt;
	data->hud.tri.p1.y_hud = data->hud.tri.p1.y_map * data->hud.yt;
	data->hud.tri.p2.x_hud = data->hud.tri.p2.x_map * data->hud.xt;
	data->hud.tri.p2.y_hud = data->hud.tri.p2.y_map * data->hud.yt;
	data->hud.tri.p3.x_hud = data->hud.tri.p3.x_map * data->hud.xt;
	data->hud.tri.p3.y_hud = data->hud.tri.p3.y_map * data->hud.yt;
}

void set_hud(t_data *data)
{
	printf("xsize:%ld\n", data->map.xsize);
	printf("data->height:%d\n", data->height);
	printf("ysiz:%ld", data->map.ysize);
	printf("data->width:%d", data->width);
	if (data->map.xsize * data->height > data->map.ysize * data->width)
	{
		data->hud.xsize = data->width / HUD_SIZE_FACTOR;
		data->hud.ysize = data->hud.xsize * data->map.ysize / data->map.xsize;
	}
	else
	{
		data->hud.ysize = data->height / HUD_SIZE_FACTOR;
		data->hud.xsize = data->hud.ysize * data->map.xsize / data->map.ysize;
	}
	data->hud.xt = data->hud.xsize / data->map.xsize;
	data->hud.yt = data->hud.ysize / data->map.ysize;
	set_triangle(data);
	data->player.posh.x = data->player.pos.x * data->hud.xt;
	data->player.posh.y = data->player.pos.y * data->hud.yt;
}
