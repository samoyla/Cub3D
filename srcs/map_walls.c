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


int	check_all_walls(t_map *map, int i, int j)
{
	if (i == 0 || map->map[i + 1] == NULL)
	      return (FAILURE);
	else if (j == 0 || map->map[j + 1] == '\0')
		return (FAILURE);
	else if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
			|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}
