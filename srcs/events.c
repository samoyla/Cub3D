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

void	update_p_clockwise(t_data *data, t_posi *p, int dir)
{
	p->x = data->player.pos.x + dir * STEP * sin(data->player.angle);
	p->y = data->player.pos.y + dir * STEP * cos(data->player.angle);
}

void	update_p_counterclockwise(t_data *data, t_posi *p, int dir)
{
	p->x = data->player.pos.x
		+ dir * STEP * sin(data->player.angle + PI / 2);
	p->y = data->player.pos.y
		+ dir * STEP * cos(data->player.angle + PI / 2);
}

void	move_player(t_data *data, int key)
{
	t_posi	p;
	t_posi	pcheck;
	int		dir;

	dir = 1;
	if (key == XK_s || key == XK_d)
		dir = -1;
	if (key == XK_w || key == XK_s)
		update_p_clockwise(data, &pcheck, dir);
	else
		update_p_counterclockwise(data, &pcheck, dir);
	if (!is_move_valid(data, pcheck))
		return ;
	if (key == XK_w || key == XK_s)
		update_p_clockwise(data, &p, dir);
	else
		update_p_counterclockwise(data, &p, dir);
	data->player.pos.x = p.x;
	data->player.pos.y = p.y;
	data->player.posh.x = data->player.pos.x * data->hud.xt;
	data->player.posh.y = data->player.pos.y * data->hud.yt;
	hud_points_update(data);
	screen_points_update(data);
}

int	handle_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
		ft_red_cross(data);
	else if (key == XK_Left || key == XK_Right)
		z_rotation_player(data, key);
	else if (key == XK_w || key == XK_a
		|| key == XK_s || key == XK_d)
		move_player(data, key);
	get_wall_height(data);
	return (0);
}

int	ft_red_cross(t_data *data)
{
	exit_free_destroy(data, NULL, SUCCESS);
}
