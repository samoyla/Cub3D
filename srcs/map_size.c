/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:17:42 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/21 18:36:08 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map_size(t_map *map)
{
	long y;
	long x;

	y = 0;
	if (map->map[0])
		x = ft_strlen(map->map[0]);
	while (map->map[(int)y])
	{
		if (ft_strlen(map->map[(int)y]) > x)
			x = ft_strlen(map->map[y]);
		y++;
		// if (y > INT_MAX)
		// 	ERROR;
	}
	map->xsize = x; // proteger le x aussi?...
	map->ysize = y;
}
