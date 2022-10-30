/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_height.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:06:53 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/30 16:55:04 by iguscett         ###   ########.fr       */
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
	return (nomin / denomin);
}

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
	d->screen.point_angle = acos(DIST / norm_two_points(d->player.pos, d->player.check)) + d->player.angle;
	if (isnan(d->screen.point_angle))
		d->screen.point_angle = d->player.angle;
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
		if (va->vx < 0)
			data->wall.side[i] = 'W';
		else
			data->wall.side[i] = 'E';
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
		if (va->vy < 0)
			data->wall.side[i] = 'N';
		else
			data->wall.side[i] = 'S';
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
	data->wall.wheight[i] = DIST / ray_dist;
	if (data->wall.wheight[i] > 1)
		data->wall.wheight[i] = 1;
}

void get_column(t_data *data, int i)
{
	if (data->wall.side[i] == 'N')
		data->wall.col[i] = (data->player.rayp.x - ceil(data->player.rayp.x) + 1);
	else if (data->wall.side[i] == 'E')
		data->wall.col[i] = (data->player.rayp.y - ceil(data->player.rayp.y) + 1);
	if (data->wall.side[i] == 'S')
		data->wall.col[i] = (ceil(data->player.rayp.x) - data->player.rayp.x);
	if (data->wall.side[i] == 'W')
		data->wall.col[i] = (ceil(data->player.rayp.y) - data->player.rayp.y);
}

void get_wall_height(t_data *data)
{
	int		wall;
	int		i;
	t_posi	w;
	t_posi	m;
	t_vect	va;

	i = -1;
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
		get_height(data, i, &va);
		get_column(data, i);
	}
}
