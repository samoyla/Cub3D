/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_and_check_struct.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 16:11:49 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map)
{
	map->size = 0;
	map->count = 0;
	map->f_red = 0;
	map->f_green = 0;
	map->f_blue = 0;
	map->c_red = 0;
	map->c_green = 0;
	map->c_blue = 0;
}

void	init_check(t_check *check)
{
	check->f = 0;
	check->c = 0;
	check->no = 0;
	check->so = 0;
	check->we = 0;
	check->ea = 0;
}

void	init_map_and_check_struct(t_data *data, t_check *check)
{
	data->fov = FOV_DEGREES * PI / 180;
	data->half = (tan(data->fov * 0.5) * DIST);
	data->max_pdist = data->half / sin(data->fov * 0.5);
	init_map(&data->map);
	init_check(check);
}
