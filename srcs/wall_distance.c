/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:06:53 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/22 16:20:42 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double abs_double(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

double wall_boundary(double coord, double dir)
{
	printf("coord:%f and dir:%f\n", coord, dir);
	if (dir > 0)
		return (ceil(coord));
	// else if (dir < 0)
	return (ceil(coord) - 1);
	// return (0); // no
}

void wall_distance(t_data *data)
{
	int wall;
	// double wx;
	// double wy;
	// double distx;
	// double disty;
	// double stepx;
	// double stepy;

	data->player.check.x = data->player.pos.x + data->player.v.vx * DIST;
	data->player.check.y = data->player.pos.y + data->player.v.vy * DIST;

	data->player.wall.x = wall_boundary(data->player.check.x, data->player.v.vx);
	data->player.wall.y = wall_boundary(data->player.check.y, data->player.v.vy);
	printf("wall x:%f y:%f\n", data->player.wall.x, data->player.wall.y);

	data->player.dist.x = abs_double(data->player.wall.x - data->player.pos.x);
	data->player.dist.y = abs_double(data->player.wall.y - data->player.pos.y);
	printf("dist x:%f y:%f\n", data->player.dist.x, data->player.dist.y);

	data->player.step.x = abs_double(data->player.dist.x / data->player.v.vx);
	data->player.step.y = abs_double(data->player.dist.y / data->player.v.vy);
	printf("step x:%f y:%f\n", data->player.step.x, data->player.step.y);

	wall = 0;
	printf("map:%c\n", data->map.map[(int)data->player.wall.y][(int)data->player.wall.x]);
	if (data->map.map[(int)data->player.wall.y][(int)data->player.wall.x] == '1')
		printf("OKKKKKKKKKKKK\n");
	if (data->player.step.x < data->player.step.y)
	{

	}
	else if (data->player.step.x >= data->player.step.y)
	{

	}


	// wall = 0
	// while (!wall)
	// {

	// }











	// int i;

	// i = -1;
	// while(++i < data->width)
	// {
	// 	// img_pix_put(&data->img, (data->screen.pleft.x  + data->screen.incr * data->screen.v.vx * i) * data->hud.xt, (data->screen.pleft.y + data->screen.incr * data->screen.v.vy * i) * data->hud.yt, STRONG_BLUE);
	// }
}
