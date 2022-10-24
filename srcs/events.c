/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/24 11:23:24 by iguscett         ###   ########.fr       */
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
	// printf("vx:%f vy:%f\n", data->screen.v.vx, data->screen.v.vy);
}


void z_angle_rotation(t_data *data, int key)
{
	int i;

	i = 0;
	while (angles[i] != -1 && data->player.angle != angles[i])
		i++;
	if (key == XK_Left)
	{
		if (i == 15)
			data->player.angle = angles[0];
		else
			data->player.angle = angles[++i];
	}
	else if (key == XK_Right)
	{
		if (i == 0)
			data->player.angle = angles[15];
		else
			data->player.angle = angles[--i];
	}
	data->player.v.vx = sin(data->player.angle);
	data->player.v.vy = cos(data->player.angle);

	// checker
	data->player.check.x = data->player.pos.x + data->player.v.vx * DIST;
	data->player.check.y = data->player.pos.y + data->player.v.vy * DIST;
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

/*
	Certainement a optimiser/ameliorer quand le raytracing sera fait
*/
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
	// printf("MAX:%f d:%f sub:%f\n", MAX_PDIST, d, d- MAX_PDIST);
	if (d - MAX_PDIST <= 0)
		return (0);
	return (1);
}

int get_min_dist_to_wall(t_data *data, t_posi pcheck)
{
	if (abs_double(pcheck.x - ceil(pcheck.x)) > abs_double(pcheck.x - (ceil(pcheck.x) - 1)))
	{
		// printf("low x:%f y:%f\n", ceil(pcheck.x) - 2, ceil(pcheck.y)-1);
		// printf("x:%f map:%c\n", abs_double(pcheck.x - (ceil(pcheck.x) - 1)), data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2]);
		if (data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x) - 2] == '1')
		{
			if (!verify_min_dist(abs_double(pcheck.x - (ceil(pcheck.x) - 1))))
			{
				// printf("111111\n");
				return (0);
			}
		}
	}
	else
	{
		if (data->map.map[(int)ceil(pcheck.y) - 1][(int)ceil(pcheck.x)] == '1')
		{
			if (!verify_min_dist(abs_double(pcheck.x - ceil(pcheck.x))))
			{
				// printf("222222\n");
				return (0);
			}
		}
	}
	if (abs_double(pcheck.y - ceil(pcheck.y)) > abs_double(pcheck.y - (ceil(pcheck.y) - 1)))
	{
		// printf("\nldist y:%f\n", abs_double(pcheck.y - (ceil(pcheck.y) - 1)));
		// printf("mapx:%f y:%f\n", ceil(pcheck.x) - 1, ceil(pcheck.y) - 2);
		// printf("m:%c\n", data->map.map[(int)ceil(pcheck.y) - 2][(int)ceil(pcheck.x) - 1]);
		if (data->map.map[(int)ceil(pcheck.y) - 2][(int)ceil(pcheck.x) - 1] == '1')
		{
			if (!verify_min_dist(abs_double(pcheck.y - (ceil(pcheck.y) - 1))))
			{
				// printf("333333\n");
				return (0);
			}
		}
	}
	else
	{
		if (data->map.map[(int)ceil(pcheck.y)][(int)ceil(pcheck.x) - 1] == '1')
		{
			if (!verify_min_dist(abs_double(pcheck.y - ceil(pcheck.y))))
			{
				// printf("444444\n");
				return (0);
			}
		}
	}
	return (1);
}

int check_minimum_distance(t_data *data, t_posi pclose)
{
	double matx;
	double maty;

	// if ()
	(void)data;
	(void)pclose;


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
	if (!get_min_dist_to_wall(data, pcheck))
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
	// printf("pos x:%f y:%f\n", data->player.pos.x, data->player.pos.y);
	// printf("screen half:%f\n", HALF);
	// printf("lscreen x:%f y:%f\n", data->screen.pleft.x, data->screen.pleft.y);
	// printf("rscreen x:%f y:%f\n", data->screen.pright.x, data->screen.pright.y);

	if (key == XK_Escape)
		ft_red_cross(data);
	else if(key == XK_Left || key == XK_Right)
		z_rotation_player(data, key);
	else if(key == XK_w || key == XK_a
		|| key == XK_s || key == XK_d)
		move_player(data, key);
	else
		printf("Key pressed:%d\n", key);

	wall_distance(data);


	return (0);
}

int	ft_red_cross(t_data *data, t_map *map)
{
	ft_free_n_destroy(data);
	//free_tab(map->decor);
	//free_tab(map->whole);
	exit (0);
}
