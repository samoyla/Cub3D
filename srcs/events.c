/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/25 17:51:09 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void screen_points_update(t_data *data)
{
	double norm;

	data->screen.pleft.x = data->player.pos.x + HALF;
	data->screen.pleft.y = data->player.pos.y + DIST;
	data->screen.pright.x = data->player.pos.x - HALF;
	data->screen.pright.y = data->player.pos.y + DIST;
	z_rotation(data, &data->screen.pleft, data->player.angle);
	z_rotation(data, &data->screen.pright, data->player.angle);
	data->screen.v.vx = data->screen.pright.x - data->screen.pleft.x;
	data->screen.v.vy = data->screen.pright.y - data->screen.pleft.y;
	norm = sqrt((data->screen.v.vx * data->screen.v.vx) + (data->screen.v.vy * data->screen.v.vy));
	data->screen.v.vx /= norm;
	data->screen.v.vy /= norm;
}


void z_angle_rotation(t_data *data, int key)
{
	int i;

	i = 0;
	while (i < NB_ANGLES && data->player.angle != data->player.angles[i])
		i++;
	if (key == XK_Left)
	{
		if (i == NB_ANGLES - 1)
			data->player.angle = data->player.angles[0];
		else
			data->player.angle = data->player.angles[++i];
	}
	else if (key == XK_Right)
	{
		if (i == 0)
			data->player.angle = data->player.angles[NB_ANGLES - 1];
		else
			data->player.angle = data->player.angles[--i];
	}
	data->player.v.vx = sin(data->player.angle);
	data->player.v.vy = cos(data->player.angle);

	// checker
	// data->player.check.x = data->player.pos.x + data->player.v.vx * DIST;
	// data->player.check.y = data->player.pos.y + data->player.v.vy * DIST;
}

void hud_points_update(t_data *data)
{
	data->hud.tri.p1.x_hud = data->player.posh.x + 0.25 * sin(data->player.angle) * data->hud.xt;
	data->hud.tri.p1.y_hud = data->player.posh.y + 0.25 * cos(data->player.angle) * data->hud.yt;
	data->hud.tri.p2.x_hud = data->player.posh.x + 0.16667 * sin(PI * 0.25 - data->player.angle) * data->hud.xt;
	data->hud.tri.p2.y_hud = data->player.posh.y - 0.16667 * cos(PI * 0.25 - data->player.angle) * data->hud.yt;
	data->hud.tri.p3.x_hud = data->player.posh.x - 0.16667 * sin(PI * 0.25 + data->player.angle) * data->hud.xt;
	data->hud.tri.p3.y_hud = data->player.posh.y - 0.16667 * cos(PI * 0.25 + data->player.angle) * data->hud.yt;
}

void z_rotation_player(t_data *data, int key)
{
	z_angle_rotation(data, key);
	hud_points_update(data);
	screen_points_update(data);
}

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

int get_min_dist_to_wall(t_data *data, t_posi pcheck)
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

void move_player(t_data *data, int key)
{
	t_posi p;
	t_posi pcheck;
	int dir;

	dir = 1;
	if (key == XK_s || key == XK_d)
		dir = -1;
	if (key == XK_w || key == XK_s)
	{
		pcheck.x = data->player.pos.x + dir * STEP * sin(data->player.angle); // Optimiser les collisions!!
		pcheck.y = data->player.pos.y + dir * STEP * cos(data->player.angle);
	}
	else
	{
		pcheck.x = data->player.pos.x + dir * (STEP + 0.1) * sin(data->player.angle + PI / 2);
		pcheck.y = data->player.pos.y + dir * (STEP + 0.1) * cos(data->player.angle + PI / 2);
	}
	// printf("P:x:%f y:%f\n", data->player.pos.x, data->player.pos.y);
	// printf("Pcheck:x:%f y:%f\n", pcheck.x, pcheck.y);
	if (!get_min_dist_to_wall(data, pcheck)) // PROBLEME: chcker la map rc_dev.c erreur en haut a gauche passe a travers mur
		return;
	// if (!is_pos_in_bounds(data, pcheck))
	// 	return;
	if (key == XK_w || key == XK_s)
	{
		p.x = data->player.pos.x + dir * STEP * sin(data->player.angle);
		p.y = data->player.pos.y + dir * STEP * cos(data->player.angle);
	}
	else
	{
		p.x = data->player.pos.x + dir * STEP * sin(data->player.angle + PI / 2);
		p.y = data->player.pos.y + dir * STEP * cos(data->player.angle + PI / 2);
	}
	data->player.pos.x = p.x;
	data->player.pos.y = p.y;
	data->player.posh.x = data->player.pos.x * data->hud.xt;
	data->player.posh.y = data->player.pos.y * data->hud.yt;
	hud_points_update(data);
	screen_points_update(data);

	// checker
	// data->player.check.x = data->player.pos.x + data->player.v.vx * DIST;
	// data->player.check.y = data->player.pos.y + data->player.v.vy * DIST;
}

int	handle_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
		ft_red_cross(data);
	else if(key == XK_Left || key == XK_Right)
		z_rotation_player(data, key);
	else if(key == XK_w || key == XK_a
		|| key == XK_s || key == XK_d)
		move_player(data, key);
	else
		printf("Key pressed:%d\n", key);

	get_wall_height(data);


	return (0);
}

int	ft_red_cross(t_data *data)
{
	ft_free_n_destroy(data);
	//free_tab(map->decor);
	//free_tab(map->whole);
	exit (0);
}
