/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/28 19:04:51 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void

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
		pcheck.x = data->player.pos.x + dir * STEP * sin(data->player.angle);
		pcheck.y = data->player.pos.y + dir * STEP * cos(data->player.angle);
	}
	else
	{
		pcheck.x = data->player.pos.x + dir * STEP * sin(data->player.angle + PI / 2);
		pcheck.y = data->player.pos.y + dir * STEP * cos(data->player.angle + PI / 2);
	}
	// printf("P:x:%f y:%f\n", data->player.pos.x, data->player.pos.y);
	// printf("Pcheck:x:%f y:%f\n", pcheck.x, pcheck.y);
	if (!is_move_valid(data, pcheck)) // PROBLEME: chcker la map rc_dev.c erreur en haut a gauche passe a travers mur
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
