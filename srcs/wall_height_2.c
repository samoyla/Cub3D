/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_height_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:06:53 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 16:45:45 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_ray_step(t_data *data, t_hcalc *st)
{
	data->player.step.x = absd((st->wall.x
				- data->player.rayp.x) / st->vangle.vx);
	data->player.step.y = absd((st->wall.y
				- data->player.rayp.y) / st->vangle.vy);
}

void	update_raypos_and_matrix_idx_x(t_data *data, t_hcalc *st)
{
	data->player.rayp.x += st->vangle.vx * data->player.step.x;
	data->player.rayp.y += st->vangle.vy * data->player.step.x;
	if (st->vangle.vx <= 0)
		st->matrix.x = st->wall.x - 1;
	else if (st->vangle.vx > 0)
		st->matrix.x = st->wall.x;
	st->matrix.y = ceil(data->player.rayp.y) - 1;
}

void	update_raypos_and_matrix_idx_y(t_data *data, t_hcalc *st)
{
	data->player.rayp.x += st->vangle.vx * data->player.step.y;
	data->player.rayp.y += st->vangle.vy * data->player.step.y;
	if (st->vangle.vy <= 0)
		st->matrix.y = st->wall.y - 1;
	else if (st->vangle.vy > 0)
		st->matrix.y = st->wall.y;
	st->matrix.x = ceil(data->player.rayp.x) - 1;
}

void	update_wall_value_and_idx_x(t_data *data, t_hcalc *st, int *wall, int i)
{
	if (data->map.map[(int)st->matrix.y][(int)st->matrix.x] == '1')
	{
		*wall = 1;
		if (st->vangle.vx < 0)
			data->wall.side[i] = 'W';
		else
			data->wall.side[i] = 'E';
	}
	if (st->vangle.vx < 0)
		st->wall.x -= 1;
	else if (st->vangle.vx > 0)
		st->wall.x += 1;
}

void	update_wall_value_and_idx_y(t_data *data, t_hcalc *st, int *wall, int i)
{
	if (data->map.map[(int)st->matrix.y][(int)st->matrix.x] == '1')
	{
		*wall = 1;
		if (st->vangle.vy < 0)
			data->wall.side[i] = 'N';
		else
			data->wall.side[i] = 'S';
	}
	if (st->vangle.vy < 0)
		st->wall.y -= 1;
	else if (st->vangle.vy > 0)
		st->wall.y += 1;
}
