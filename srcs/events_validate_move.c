/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_validate_move.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/28 19:00:33 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_pos_in_bounds(t_data *data, t_posi p)
{
	if ((int)p.x > data->map.xsize || (int)p.y > data->map.ysize)
		return (0);
	if (data->map.map[(int)p.y][(int)p.x] == '1')
		return (0);
	return (1);
}

int verify_min_dist(double d)
{
	if (d - MAX_PDIST <= 0)
		return (0);
	return (1);
}

int is_in_corner(t_posi pcheck)
{
	int corner;

	corner = 0;
	if (pcheck.x - ceil(pcheck.x) + 1 <= MAX_PDIST || pcheck.x - ceil(pcheck.x) + 1 >= 1 - MAX_PDIST)
		corner++;
	if (pcheck.y - ceil(pcheck.y) + 1 <= MAX_PDIST || pcheck.y - ceil(pcheck.y) + 1 >= 1 - MAX_PDIST)
		corner++;
	if (corner == 2)
		return (1);
	return (0);
}

int corner_ok(t_data *data, t_posi pcheck)
{
	int x;
	int y;
	int dx;
	int dy;

	x = ceil(pcheck.x) - 1;
	y = ceil(pcheck.y) - 1;
	dx = 1;
	dy = 1;
	if (pcheck.x - ceil(pcheck.x) + 1 <= MAX_PDIST)
		dx = - 1;
	if (pcheck.y - ceil(pcheck.y) + 1 <= MAX_PDIST)
		dy = - 1;
	// printf("px:%f py:%f\n", pcheck.x, pcheck.y);
	// printf("1[%d][%d] 2[%d][%d] 3[%d][%d] 4[%d][%d]\n", y,x,y,x+dx,y+dy,x,y+dy,x+dx);
	// printf("m1:%c m2:%c m3:%c m4:%c\n", data->map.map[y][x], data->map.map[y][x+dx], data->map.map[y+dy][x], data->map.map[y+dy][x+dx]);
	if (data->map.map[y][x] == '1' || data->map.map[y][x + dx] == '1'
		|| data->map.map[y + dy][x] == '1' || data->map.map[y + dy][x + dx] == '1')
		return (0);
	return (1);
}

int is_move_valid(t_data *data, t_posi pcheck)
{
	// printf("_________________\nPcheck x:%f y:%f\n", pcheck.x, pcheck.y);
	if (absd(pcheck.x - ceil(pcheck.x)) > absd(pcheck.x - (ceil(pcheck.x) - 1)))
	{
		// printf("X low x:%f y:%f\n", ceil(pcheck.x) - 2, ceil(pcheck.y)-1);
		// printf("x:%f map:%c\n\n", absd(pcheck.x - (ceil(pcheck.x) - 1)), data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2]);
		if (data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2] == '1')
		{
			if (!verify_min_dist(absd(pcheck.x - (ceil(pcheck.x) - 1))))
				return (0);
		}
	}
	else
	{
		// printf("X hig x:%f y:%f\n", ceil(pcheck.x) - 2, ceil(pcheck.y)-1);
		// printf("x:%f map:%c\n\n", absd(pcheck.x - (ceil(pcheck.x) - 1)), data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2]);
		if (data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x)] == '1')
		{
			if (!verify_min_dist(absd(pcheck.x - ceil(pcheck.x))))
				return (0);
		}
	}
	if (absd(pcheck.y - ceil(pcheck.y)) > absd(pcheck.y - (ceil(pcheck.y) - 1)))
	{
		// printf("Y low x:%f y:%f\n", ceil(pcheck.x) - 2, ceil(pcheck.y)-1);
		// printf("x:%f map:%c\n\n", absd(pcheck.x - (ceil(pcheck.x) - 1)), data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2]);
		if (data->map.map[(int)ceil(pcheck.y) - 2][(int)ceil(pcheck.x) - 1] == '1')
		{
			if (!verify_min_dist(absd(pcheck.y - (ceil(pcheck.y) - 1))))
				return (0);
		}
	}
	else
	{
		// printf("Y hig x:%f y:%f\n", ceil(pcheck.x) - 2, ceil(pcheck.y)-1);
		// printf("x:%f map:%c\n\n", absd(pcheck.x - (ceil(pcheck.x) - 1)), data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2]);
		if (data->map.map[(int)ceil(pcheck.y)][(int)ceil(pcheck.x) - 1] == '1')
		{
			if (!verify_min_dist(absd(pcheck.y - ceil(pcheck.y))))
				return (0);
		}
	}
	if (is_in_corner(pcheck) && !corner_ok(data, pcheck))
		return (0);
	// printf("-----\n");
	return (1);
}
