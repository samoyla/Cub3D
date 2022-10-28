/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:06:53 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/28 16:30:51 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double norm_two_points(t_posi p1, t_posi p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y)));
}

double absd(double a)
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

double two_vect_angle(t_vect va, t_vect vb)
{
	double nomin;
	double denomin;

	nomin = va.vx * vb.vx + va.vy * vb.vy;
	denomin = (sqrt(va.vx * va.vx + vb.vx * vb.vx)) * (sqrt(va.vy * va.vy + vb.vy * vb.vy));
	// printf("nomin:%f denomin:%f nomin/denomin:%f\n", nomin, denomin, nomin / denomin);
	return (nomin / denomin);
}

////////////////////////////////////////////////////

void init_start_and_ray_points(t_data *d, t_posi *w, int i, int *wall, t_vect *va)
{
	double norm;

	*wall = 0;
	d->player.check.x = d->screen.pleft.x + d->screen.xincr * d->screen.v.vx * i;
	d->player.check.y = d->screen.pleft.y + d->screen.yincr * d->screen.v.vy * i;

	va->vx = d->player.check.x - d->player.pos.x;
	va->vy = d->player.check.y - d->player.pos.y;
	norm = sqrt((va->vx * va->vx) + (va->vy * va->vy));
	va->vx /= norm;
	va->vy /= norm;

	// if (i >= 639 && i <= 641)
	// 	printf("\nfor acos:%f and acos:%f\n", DIST / norm_two_points(d->player.pos, d->player.check), acos(DIST / norm_two_points(d->player.pos, d->player.check)));
	d->screen.point_angle = acos(DIST / norm_two_points(d->player.pos, d->player.check)) + d->player.angle;
	if (isnan(d->screen.point_angle))
		d->screen.point_angle = d->player.angle; //////////////////////////
	d->player.rayp.x = d->player.check.x;
	d->player.rayp.y = d->player.check.y;
	w->x = wall_boundary(d->player.rayp.x, va->vx);
	w->y = wall_boundary(d->player.rayp.y, va->vy);
}

void get_dist_and_step(t_data *data, t_vect *va)
{
	data->player.dist.x = absd(data->player.wall.x - data->player.rayp.x);
	data->player.dist.y = absd(data->player.wall.y - data->player.rayp.y);
	data->player.step.x = absd(data->player.dist.x / va->vx);
	data->player.step.y = absd(data->player.dist.y / va->vy);
}

void update_raypos_and_matrix_idx_x(t_data *data, t_posi w, t_posi *m, t_vect *va)
{
	data->player.rayp.x += va->vx * data->player.step.x;
	data->player.rayp.y += va->vy * data->player.step.x;
	if (va->vx <= 0) // protect
		m->x = w.x - 1;
	else if (va->vx > 0)
		m->x = w.x;
	m->y = ceil(data->player.rayp.y) - 1;
}

void update_raypos_and_matrix_idx_y(t_data *data, t_posi w, t_posi *m, t_vect *va)
{
	data->player.rayp.x += va->vx * data->player.step.y;
	data->player.rayp.y += va->vy * data->player.step.y;
	if (va->vy <= 0) // protect
		m->y = w.y - 1;
	else if (va->vy > 0)
		m->y = w.y;
	m->x = ceil(data->player.rayp.x) - 1;
}

void update_ray_step(t_data *data, t_posi w, t_vect *va)
{
	data->player.step.x = absd((w.x - data->player.rayp.x) / va->vx);
	data->player.step.y = absd((w.y - data->player.rayp.y) / va->vy);
}

void update_wall_value_and_idx_x(t_data *data, t_posi *w, t_posi *m, int *wall, int i, t_vect *va)
{
	if (data->map.map[(int)m->y][(int)m->x] == '1')
	{
		*wall = 1;
		data->wallnb[i] = (int)(m->y * 10) + (int)m->x;
		if (va->vx < 0)
			data->side[i] = 'W';
		else
			data->side[i] = 'E';
	}
	if (va->vx < 0)
		w->x -= 1;
	else if (va->vx > 0)
		w->x += 1;
}

void update_wall_value_and_idx_y(t_data *data, t_posi *w, t_posi *m, int *wall, int i, t_vect *va)
{
	if (data->map.map[(int)m->y][(int)m->x] == '1')
	{
		*wall = 1;
		data->wallnb[i] = (int)(m->y * 10) + (int)m->x;
		if (va->vy < 0)
			data->side[i] = 'N';
		else
			data->side[i] = 'S';
	}
	if (va->vy < 0)
		w->y -= 1;
	else if (va->vy > 0)
		w->y += 1;
}

void get_height(t_data *data, int i, t_vect *va)
{
	double ray_dist;


	ray_dist = norm_two_points(data->player.check, data->player.rayp) * cos(data->screen.point_angle - data->player.angle);
	data->wheight[i] = DIST / ray_dist;
	if (data->wheight[i] > 1)
		data->wheight[i] = 1;
	// if (i >= 639 && i <= 641)
	// {
	// 	printf("i:%d ray_dist:%f wheight:%f\n", i, ray_dist, data->wheight[i]);
	// }
}

void get_column(t_data *data, int i)
{
	if (data->side[i] == 'N')
		data->col[i] = (data->player.rayp.x - ceil(data->player.rayp.x) + 1);
	else if (data->side[i] == 'E')
		data->col[i] = (data->player.rayp.y - ceil(data->player.rayp.y) + 1);
	if (data->side[i] == 'S')
		data->col[i] = (ceil(data->player.rayp.x) - data->player.rayp.x);
	if (data->side[i] == 'W')
		data->col[i] = (ceil(data->player.rayp.y) - data->player.rayp.y);
}

void get_wall_height(t_data *data)
{
	int		wall;
	int		i;
	t_posi	w;
	t_posi	m;
	t_vect	va;

	i = -1;
	// printf("----------------------------------------\n--------------------\n");
	while(++i < data->width)
	{
		init_start_and_ray_points(data, &w, i, &wall, &va);
		while (!wall)
		{
			update_ray_step(data, w, &va);
			if (data->player.step.x < data->player.step.y)
			{
				update_raypos_and_matrix_idx_x(data, w, &m, &va);
				update_wall_value_and_idx_x(data, &w, &m, &wall, i, &va);
			}
			else if (data->player.step.x >= data->player.step.y)
			{
				update_raypos_and_matrix_idx_y(data, w, &m, &va);
				update_wall_value_and_idx_y(data, &w, &m, &wall, i, &va);
			}
		}
		get_height(data, i, &va); // OK
		get_column(data, i);
		// if (i >= 639 && i <= 641)
		// 	printf("i:%d height:%f col:%f\n", i, data->wheight[i], data->col[i]);
	}
}
















// 111111111111111111111111111111111111111111111111111111111111111111111111111111111

// void get_wall_height(t_data *data)
// {
// 	int		wall;
// 	int		i;
// 	t_posi	w;
// 	t_posi	m;

// 	// int limit = 0;
// 	i = -1;
// 	while(++i < data->width)
// 	{
// 		// i = 640;
// 		init_start_and_ray_points(data, &w, i);
// 		wall = 0;
// 		while (!wall)
// 		{
// 			// get_matrix_indexes(data);
// 			data->player.dist.x = absd(w.x - data->player.rayp.x);
// 			data->player.dist.y = absd(w.y - data->player.rayp.y);
// 			data->player.step.x = absd(data->player.dist.x / data->player.v.vx);
// 			data->player.step.y = absd(data->player.dist.y / data->player.v.vy);
// 			// printf("RAY pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 			// printf("dist x:%f y:%f\n", data->player.dist.x, data->player.dist.y);
// 			// printf("step x:%f y:%f\n", data->player.step.x, data->player.step.y);
// 			if (data->player.step.x < data->player.step.y)
// 			{
// 				data->player.rayp.x += data->player.v.vx * data->player.step.x;
// 				data->player.rayp.y += data->player.v.vy * data->player.step.x;
// 				get_matrix_indexes_x(data, w, &m);
// 				// printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 				// printf(">X my:%f mx:%f", m.y, m.x);
// 				// printf(" m:%c\n", data->map.map[(int)m.y][(int)m.x]);
// 				if (data->map.map[(int)m.y][(int)m.x] == '1') // proteger les indices!! car Maryna a seg ici
// 					wall = 1;
// 				if (data->player.v.vx < 0 && w.x > 0)
// 					w.x -= 1;
// 				else if (data->player.v.vx > 0)
// 					w.x += 1;
// 				// if (data->player.v.vy > 0)
// 				// 	w.y += 1;
// 			}
// 			else if (data->player.step.x >= data->player.step.y)
// 			{
// 				data->player.rayp.x += data->player.v.vx * data->player.step.y;
// 				data->player.rayp.y += data->player.v.vy * data->player.step.y;
// 				get_matrix_indexes_y(data, w, &m);
// 				// printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 				// printf(">Y my:%f mx:%f", m.y, m.x);
// 				// printf(" m:%c\n", data->map.map[(int)m.y][(int)m.x]);
// 				if (data->map.map[(int)m.y][(int)m.x] == '1')
// 					wall = 1;
// 				if (data->player.v.vy < 0)
// 					w.y -= 1;
// 				else if ( data->player.v.vy > 0)
// 					w.y += 1;
// 				// if (data->player.v.vx > 0)
// 				// 	w.x += 1;
// 			}
// 			// printf("----");
// 		}
// 		data->screen.dist[i] = norm_two_points(data->player.check, data->player.rayp);
// 		data->screen.wheight[i] = DIST / data->screen.dist[i];
// 		// if (limit == 10)
// 			// printf("----FFUUUUCKKKKKED UPPPPPPPPPPP----");
// 		// printf("limit:%d", limit);
// 		// printf("RAY check x:%f y:%f\n", data->player.check.x, data->player.check.y);
// 		// printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
// 		// printf("dist:%f h:%f\n\n", data->screen.dist[i], data->screen.wheight[i]);


// 		// printf("dist:%f and wheight:%f\n", data->screen.dist[i], data->screen.wheight[i]);
// 	}




// 	// GET SIZE ON SCREEN

// }



// 00000000000000000000000000000000000000000000000000000000000000000000000000000000000


// printf("wall y:%f x:%f\n", data->player.wall.y, data->player.wall.x);
			// printf("ray pos x:%f y:%f\n", data->player.rayp.x, data->player.rayp.y);
			// printf("v x:%f y:%f\n", data->player.v.vx, data->player.v.vy);



//--------------------------------------------------------------------------------------------------------------
// void get_wall_height(t_data *data)
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
// 		data->player.dist.x = absd(data->player.wall.x - data->player.rayp.x);
// 		data->player.dist.y = absd(data->player.wall.y - data->player.rayp.y);
// 		// printf("dist x:%f y:%f\n", data->player.dist.x, data->player.dist.y);
// 		data->player.step.x = absd(data->player.dist.x / data->player.v.vx);
// 		data->player.step.y = absd(data->player.dist.y / data->player.v.vy);
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
