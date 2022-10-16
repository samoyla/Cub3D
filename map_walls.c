/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:14:43 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/16 17:22:31 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	check_top_n_bottom(t_map *map)
{
	int	i;
	int	size;

	i = -1
	size = ft_strlen();
	while (map->map[0][++i])
	{	
		
	}
}

int	check_all_walls(t_map *map)
{
	if (check_top_n_bottom(map) == FAILURE)
		return(FAILURE);
	//check_left_wall(map);
	//check_right_wall(map);
	return (SUCCESS);
}
