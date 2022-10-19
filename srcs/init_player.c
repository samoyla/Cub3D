/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:36:16 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/19 14:34:57 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_player_init_pos(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void set_player_angle(t_data *data, char c)
{
	if (c == 'N')
		data->player.angle = angles[8];
	else if (c == 'S')
		data->player.angle = angles[0];
	else if (c == 'E')
		data->player.angle = angles[4];
	else if (c == 'W')
		data->player.angle = angles[12];
}

void init_player(t_data *data)
{
	int y;
	int x;

	data->player.pos.x = 0;
	data->player.pos.y = 0;
	data->player.pos.z = 0.5;
	data->player.posh.z = 0.5;
	y = -1;
	while (data->map.map[++y] && !data->player.pos.x)
	{
		x = -1;
		while (data->map.map[y][++x] && !data->player.pos.x)
		{
			if (is_player_init_pos(data->map.map[y][x]))
			{
				data->player.pos.x = x + 0.5;
				data->player.pos.y = y + 0.5;
				set_player_angle(data, data->map.map[y][x]);
			}
		}
	}
}
