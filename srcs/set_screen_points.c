/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:11:32 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/24 15:44:40 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_screen_points(t_data *data)
{
	double norm;

	data->screen.pleft.x = data->player.pos.x + HALF;
	data->screen.pleft.y = data->player.pos.y + DIST;
	data->screen.pright.x = data->player.pos.x - HALF;
	data->screen.pright.y = data->player.pos.y + DIST;
	z_rotation(data, &data->screen.pleft, data->player.angle);
	z_rotation(data, &data->screen.pright, data->player.angle);
	data->screen.xincr = (HALF * 2) / data->width;
	data->screen.fullh = data->screen.xincr * data->height;
	data->screen.yincr = data->screen.fullh / data->height;

	printf("FULL:%f xincr:%f width:%d width*xincr:%f\n", 2 * HALF, data->screen.xincr, data->width, data->width*data->screen.xincr);
	printf("y full:%f yincr:%f full(multiplication):%f\n", data->screen.fullh, data->screen.yincr, data->screen.yincr * data->height);

	data->screen.pleft.z = 0.5;
	data->screen.v.vx = data->screen.pright.x - data->screen.pleft.x;
	data->screen.v.vy = data->screen.pright.y - data->screen.pleft.y;
	norm = sqrt((data->screen.v.vx * data->screen.v.vx) + (data->screen.v.vy * data->screen.v.vy));
	data->screen.v.vx /= norm;
	data->screen.v.vy /= norm;
	// printf("vx:%f vy:%f\n", data->screen.v.vx, data->screen.v.vy);
}
