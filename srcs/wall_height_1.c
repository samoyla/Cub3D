/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_height_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:06:53 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 16:24:01 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	wall_boundary(double coord, double dir)
{
	if (dir > 0)
		return (ceil(coord));
	return (ceil(coord) - 1);
}

void	init_start_and_ray_points(t_data *d, t_hcalc *st, int *wall, int i)
{
	double	norm;

	*wall = 0;
	d->player.check.x = d->screen.pleft.x
		+ d->screen.xincr * d->screen.v.vx * i;
	d->player.check.y = d->screen.pleft.y
		+ d->screen.yincr * d->screen.v.vy * i;
	st->vangle.vx = d->player.check.x - d->player.pos.x;
	st->vangle.vy = d->player.check.y - d->player.pos.y;
	norm = sqrt((st->vangle.vx * st->vangle.vx)
			+ (st->vangle.vy * st->vangle.vy));
	st->vangle.vx /= norm;
	st->vangle.vy /= norm;
	d->screen.point_angle = acos(DIST / norm_two_points(d->player.pos,
				d->player.check)) + d->player.angle;
	if (isnan(d->screen.point_angle))
		d->screen.point_angle = d->player.angle;
	d->player.rayp.x = d->player.check.x;
	d->player.rayp.y = d->player.check.y;
	st->wall.x = wall_boundary(d->player.rayp.x, st->vangle.vx);
	st->wall.y = wall_boundary(d->player.rayp.y, st->vangle.vy);
}

void	get_height(t_data *data, int i, t_vect *va)
{
	double	ray_dist;

	ray_dist = norm_two_points(data->player.check, data->player.rayp)
		* cos(data->screen.point_angle - data->player.angle);
	data->wall.wheight[i] = DIST / ray_dist;
	if (data->wall.wheight[i] > 1)
		data->wall.wheight[i] = 1;
}

void	get_column(t_data *data, int i)
{
	if (data->wall.side[i] == 'N')
		data->wall.col[i] = (data->player.rayp.x
				- ceil(data->player.rayp.x) + 1);
	else if (data->wall.side[i] == 'E')
		data->wall.col[i] = (data->player.rayp.y
				- ceil(data->player.rayp.y) + 1);
	if (data->wall.side[i] == 'S')
		data->wall.col[i] = (ceil(data->player.rayp.x) - data->player.rayp.x);
	if (data->wall.side[i] == 'W')
		data->wall.col[i] = (ceil(data->player.rayp.y) - data->player.rayp.y);
}

void	get_wall_height(t_data *data)
{
	int		wall;
	int		i;
	t_hcalc	st;

	i = -1;
	while (++i < data->width)
	{
		init_start_and_ray_points(data, &st, &wall, i);
		while (!wall)
		{
			update_ray_step(data, &st);
			if (data->player.step.x < data->player.step.y)
			{
				update_raypos_and_matrix_idx_x(data, &st);
				update_wall_value_and_idx_x(data, &st, &wall, i);
			}
			else if (data->player.step.x >= data->player.step.y)
			{
				update_raypos_and_matrix_idx_y(data, &st);
				update_wall_value_and_idx_y(data, &st, &wall, i);
			}
		}
		get_height(data, i, &st.vangle);
		get_column(data, i);
	}
}
