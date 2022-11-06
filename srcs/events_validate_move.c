/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_validate_move.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 16:44:09 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_pos_in_bounds(t_data *data, t_posi p)
{
	if ((int)p.x > data->map.xsize || (int)p.y > data->map.ysize)
		return (0);
	if (data->map.map[(int)p.y][(int)p.x] == '1')
		return (0);
	return (1);
}

int	verify_min_dist(t_data *data, double d)
{
	if (d - data->max_pdist <= 0)
		return (0);
	return (1);
}

int	is_in_corner(t_data *data, t_posi pcheck)
{
	int	corner;

	corner = 0;
	if (pcheck.x - ceil(pcheck.x) + 1 <= data->max_pdist
		|| pcheck.x - ceil(pcheck.x) + 1 >= 1 - data->max_pdist)
		corner++;
	if (pcheck.y - ceil(pcheck.y) + 1 <= data->max_pdist
		|| pcheck.y - ceil(pcheck.y) + 1 >= 1 - data->max_pdist)
		corner++;
	if (corner == 2)
		return (1);
	return (0);
}

int	corner_ok(t_data *data, t_posi pcheck)
{
	int	x;
	int	y;
	int	dx;
	int	dy;

	x = ceil(pcheck.x) - 1;
	y = ceil(pcheck.y) - 1;
	dx = 1;
	dy = 1;
	if (pcheck.x - ceil(pcheck.x) + 1 <= data->max_pdist)
		dx = -1;
	if (pcheck.y - ceil(pcheck.y) + 1 <= data->max_pdist)
		dy = -1;
	if (data->map.map[y][x] == '1' || data->map.map[y][x + dx] == '1'
		|| data->map.map[y + dy][x] == '1'
		|| data->map.map[y + dy][x + dx] == '1')
		return (0);
	return (1);
}

int	is_move_valid(t_data *data, t_posi pcheck)
{
	if (absd(pcheck.x - ceil(pcheck.x)) > absd(pcheck.x - (ceil(pcheck.x) - 1))
		&& (data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2]
		== '1')
	&& (!verify_min_dist(data, absd(pcheck.x - (ceil(pcheck.x) - 1)))))
		return (0);
	else if (data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x)] == '1'
		&& (!verify_min_dist(data, absd(pcheck.x - ceil(pcheck.x)))))
		return (0);
	if (absd(pcheck.y - ceil(pcheck.y)) > absd(pcheck.y - (ceil(pcheck.y) - 1))
		&& (data->map.map[(int)ceil(pcheck.y) - 2][(int)ceil(pcheck.x) - 1]
		== '1')
	&& (!verify_min_dist(data, absd(pcheck.y - (ceil(pcheck.y) - 1)))))
		return (0);
	else if (data->map.map[(int)ceil(pcheck.y)][(int)ceil(pcheck.x) - 1] == '1'
		&& (!verify_min_dist(data, absd(pcheck.y - ceil(pcheck.y)))))
		return (0);
	if (is_in_corner(data, pcheck) && !corner_ok(data, pcheck))
		return (0);
	return (1);
}
