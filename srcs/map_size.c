/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:17:42 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/18 12:25:09 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_map_size(t_map *map)
{
	int y;
	int x;

	y = -1;
	if (map->map[0])
		x = ft_strlen(map->map[0]);
	while (map->map[++y])
	{
		if (ft_strlen(map->map[y]) > x)
			x = ft_strlen(map->map[y]);
	}
	map->xsize = x;
	map->ysize = y;
}
