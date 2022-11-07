/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:36:16 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 17:16:50 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_init_pos(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	set_player_angle(t_data *data, char c)
{
	if (c == 'S')
		data->player.angle = data->player.angles[0];
	else if (c == 'E')
		data->player.angle = data->player.angles[NB_ANGLES / 4];
	else if (c == 'N')
		data->player.angle = data->player.angles[NB_ANGLES / 2];
	else if (c == 'W')
		data->player.angle = data->player.angles[NB_ANGLES * 3 / 4];
	data->player.v.vx = sin(data->player.angle);
	data->player.v.vy = cos(data->player.angle);
}

void	init_player(t_data *data)
{
	int	y;
	int	x;

	data->player.angles = malloc(sizeof(data->player.angles) *(NB_ANGLES));
	if (data->player.angles == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	x = -1;
	while (++x < NB_ANGLES)
		data->player.angles[x] = x * 2 * PI / NB_ANGLES;
	data->player.pos.x = 0;
	data->player.pos.y = 0;
	y = -1;
	while (data->map.map[++y] && !data->player.pos.x)
	{
		x = -1;
		while (data->map.map[y][++x] && !data->player.pos.x)
		{
			if (is_player_init_pos(data->map.map[y][x]))
			{
				data->player.pos.x = (x + 0.5);
				data->player.pos.y = (y + 0.5);
				set_player_angle(data, data->map.map[y][x]);
			}
		}
	}
}
