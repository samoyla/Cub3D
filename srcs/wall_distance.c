/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_distance.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:06:53 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/24 23:44:10 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double norm_two_points(t_posi p1, t_posi p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

double abs_double(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

double wall_boundary(double coord, double dir)
{
	if (dir > 0)
		return (ceil(coord));
	return (ceil(coord) - 1);
}

void init_start_and_ray_points(t_data *d, int i)
{
	d->player.check.x = d->screen.pleft.x  + d->screen.xincr * d->screen.v.vx * i;
	d->player.check.y = d->screen.pleft.y + d->screen.xincr * d->screen.v.vy * i;
	d->player.rayp.x = d->player.check.x;
	d->player.rayp.y = d->player.check.y;
	d->player.wall.x = wall_boundary(d->player.rayp.x, d->player.v.vx);
	d->player.wall.y = wall_boundary(d->player.rayp.y, d->player.v.vy);
}
void get_matrix_indexes(t_data *data)
{
	if (data->player.v.vx <= 0 && data->player.wall.x > 0)
		data->player.matpos.x = data->player.wall.x - 1;
	else if (data->player.v.vx > 0)
		data->player.matpos.x = data->player.wall.x;
	if (data->player.v.vy <= 0 && data->player.wall.y > 0)
		data->player.matpos.y = data->player.wall.y - 1;
	else if (data->player.v.vy > 0 && data->player.wall.y < data->map.ysize -1)
		data->player.matpos.y = data->player.wall.y;
	if (data->player.matpos.x == data->map.xsize)
		data->player.matpos.x -= 1;
}

void get_dist_and_step(t_data *data)
{
	data->player.dist.x = abs_double(data->player.wall.x - data->player.rayp.x);
	data->player.dist.y = abs_double(data->player.wall.y - data->player.rayp.y);
	data->player.step.x = abs_double(data->player.dist.x / data->player.v.vx);
	data->player.step.y = abs_double(data->player.dist.y / data->player.v.vy);
}

void wall_distance(t_data *data)
{
	int wall;
	int i;

	int limit = 0;
	// i = -1;
	// while(++i < data->width)
	// {
		i = 640;
		init_start_and_ray_points(data, i);
		wall = 0;
		while (!wall && limit++ < 10)
		{
			get_matrix_indexes(data);
			data->player.dist.x = abs_double(data->player.wall.x - data->player.rayp.x);
			data->player.dist.y = abs_double(data->player.wall.y - data->player.rayp.y);
			data->player.step.x = abs_double(data->player.dist.x / data->player.v.vx);
			data->player.step.y = abs_double(data->player.dist.y / data->player.v.vy);
			if (data->player.step.x < data->player.step.y)
			{
				data->player.rayp.x += data->player.v.vx * data->player.step.x;
				data->player.rayp.y += data->player.v.vy * data->player.step.x;
				data->player.wall.y = ceil(data->player.rayp.y) - 1;
				printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
				printf("X ceily:%f mpx:%f\n", ceil(data->player.rayp.y) - 1, data->player.matpos.x);
				if (data->map.map[(int)(ceil(data->player.rayp.y) - 1)][(int)data->player.matpos.x] == '1') // proteger les indices!! car Maryna a seg ici
					wall = 1;
				if (data->player.v.vx < 0 && data->player.wall.x > 0)
					data->player.wall.x -= 1;
				else if (data->player.v.vx > 0 && data->player.wall.x < data->map.xsize -1)
					data->player.wall.x += 1;
				if ( data->player.v.vy > 0 && data->player.wall.y < data->map.ysize -1)
					data->player.wall.y += 1;
			}
			else if (data->player.step.x >= data->player.step.y)
			{
				data->player.rayp.x += data->player.v.vx * data->player.step.y;
				data->player.rayp.y += data->player.v.vy * data->player.step.y;
				printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
				printf("Y mpy:%f ceilx:%f\n", data->player.matpos.y, ceil(data->player.rayp.x) - 1);
				if (data->map.map[(int)data->player.matpos.y][(int)(ceil(data->player.rayp.x) - 1)] == '1')
					wall = 1;
				if (data->player.v.vy < 0 && data->player.wall.y > 0)
					data->player.wall.y -= 1;
				else if ( data->player.v.vy > 0 && data->player.wall.y < data->map.ysize -1)
					data->player.wall.y += 1;
				if (data->player.v.vx > 0 && data->player.wall.x < data->map.xsize -1)
					data->player.wall.x += 1;
			}
			printf("----");
		}
		data->screen.dist[i] = norm_two_points(data->player.check, data->player.rayp);
		data->screen.wheight[i] = DIST / data->screen.dist[i];
		// if (limit == 10)
			// printf("----FFUUUUCKKKKKED UPPPPPPPPPPP----");
		printf("limit:%d", limit);
		printf("dist:%f h:%f\n\n", data->screen.dist[i], data->screen.wheight[i]);


		// printf("dist:%f and wheight:%f\n", data->screen.dist[i], data->screen.wheight[i]);
	// }




	// GET SIZE ON SCREEN

}







// printf("wall y:%f x:%f\n", data->player.wall.y, data->player.wall.x);
			// printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
			// printf("v x:%f y:%f\n", data->player.v.vx, data->player.v.vy);



//--------------------------------------------------------------------------------------------------------------
// void wall_distance(t_data *data)
// {
// 	int wall;
// 	double dist;
// 	// double wx;
// 	// double wy;
// 	// double distx;
// 	// double disty;
// 	// double stepx;
// 	// double stepy;

// 	// POINT
// 	data->player.check.x = data->player.pos.x + data->player.v.vx * DIST;
// 	data->player.check.y = data->player.pos.y + data->player.v.vy * DIST;

// 	data->player.rayp.x = data->player.check.x;
// 	data->player.rayp.y = data->player.check.y;
// 	// printf("check x:%f y:%f\n", data->player.check.x, data->player.check.y);

// 	data->player.wall.x = wall_boundary(data->player.rayp.x, data->player.v.vx);
// 	data->player.wall.y = wall_boundary(data->player.rayp.y, data->player.v.vy);
// 	// printf("wall x:%f y:%f\n", data->player.wall.x, data->player.wall.y);

// 	wall = 0;
// 	while (!wall)
// 	{
// 		// data->player.wall.x = wall_boundary(data->player.rayp.x, data->player.v.vx);
// 		// data->player.wall.y = wall_boundary(data->player.rayp.y, data->player.v.vy);
// 		// printf("\nray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 		data->player.dist.x = abs_double(data->player.wall.x - data->player.rayp.x);
// 		data->player.dist.y = abs_double(data->player.wall.y - data->player.rayp.y);
// 		// printf("dist x:%f y:%f\n", data->player.dist.x, data->player.dist.y);
// 		data->player.step.x = abs_double(data->player.dist.x / data->player.v.vx);
// 		data->player.step.y = abs_double(data->player.dist.y / data->player.v.vy);
// 		// printf("step x:%f y:%f\n", data->player.step.x, data->player.step.y);
// 		// printf("wy:%f x:%f map:%c\n", data->player.wall.y, data->player.wall.x,data->map.map[(int)data->player.wall.y][(int)data->player.wall.x]);
// 		if (data->player.step.x < data->player.step.y)
// 		{
// 			printf("\nray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 			data->player.rayp.x += data->player.v.vx * data->player.step.x;
// 			data->player.rayp.y += data->player.v.vy * data->player.step.x;
// 			data->player.wall.y = ceil(data->player.rayp.y) - 1;
// 			if (data->player.v.vx < 0 && data->player.wall.x > 0)
// 				data->player.wall.x -= 1;
// 			printf("twy:%f x:%f\n", data->player.wall.y, data->player.wall.x);
// 			printf("twy:%f x:%f map:%c\n", data->player.wall.y, data->player.wall.x,data->map.map[(int)data->player.wall.y][(int)data->player.wall.x]);
// 			if (data->map.map[(int)data->player.wall.y][(int)data->player.wall.x] == '1')
// 				wall = 1;
// 			if (data->player.v.vx < 0 && data->player.wall.x > 0)
// 				data->player.wall.x = wall_boundary(data->player.rayp.x, data->player.v.vx);
// 			else if (data->player.wall.x < data->map.xsize -1)
// 				data->player.wall.x += 1;
// 		}
// 		else if (data->player.step.x >= data->player.step.y)
// 		{
// 			printf("\nray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 			data->player.rayp.x += data->player.v.vx * data->player.step.y;
// 			data->player.rayp.y += data->player.v.vy * data->player.step.y;
// 			data->player.wall.x = ceil(data->player.rayp.x) - 1;
// 			if (data->player.v.vy < 0 && data->player.wall.y > 0)
// 				data->player.wall.y -= 1;
// 			printf("twy:%f x:%f\n", data->player.wall.y, data->player.wall.x);
// 			printf("twy:%f x:%f map:%c\n", data->player.wall.y, data->player.wall.x,data->map.map[(int)data->player.wall.y][(int)data->player.wall.x]);
// 			if (data->map.map[(int)data->player.wall.y][(int)data->player.wall.x] == '1')
// 				wall = 1;
// 			if (data->player.v.vy < 0 && data->player.wall.y > 0)
// 				data->player.wall.y = wall_boundary(data->player.rayp.y, data->player.v.vy);
// 			else if (data->player.wall.y < data->map.ysize -1)
// 				data->player.wall.y += 1;
// 			// if (!wall && data->player.wall.y < data->map.ysize -1)
// 			// 	data->player.wall.y += 1;
// 		}
// 		// if (!wall && data->player.wall.x < data->map.xsize -1)
// 		// 	data->player.wall.x += 1;
// 		// if (!wall && data->player.wall.y < data->map.ysize -1)
// 		// 	data->player.wall.y += 1;
// 		// printf("\nrayp x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 		// printf("wall x:%f y:%f\n", data->player.wall.x, data->player.wall.y);
// 	}
// 	dist = norm_two_points(data->player.check, data->player.rayp);
// 	printf("Final dist:%f\n", dist);

// 	// wall = 0 // HEEEEEEEEEEEEEEEEEEEEEEEEERE HERE-------------------------------<<<<<
// 	// while (!wall)
// 	// {

// 	// }











// 	// int i;

// 	// i = -1;
// 	// while(++i < data->width)
// 	// {
// 	// 	// img_pix_put(&data->img, (data->screen.pleft.x  + data->screen.incr * data->screen.v.vx * i) * data->hud.xt, (data->screen.pleft.y + data->screen.incr * data->screen.v.vy * i) * data->hud.yt, STRONG_BLUE);
// 	// }
// }
