/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:34:56 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/09 15:56:53 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_tx(t_map *map)
{
	int		i;
	char	**wind_rose;
	
	i = 0;
	wind_rose = NULL;
	while(map->tx[i] && i < 6)
	{
		wind_rose = ft_split(map->tx[i], ' ');
		printf("%s\n", wind_rose[i]);
		if (strncmp(wind_rose[0], "NO", 3) == 0)
			map->no = strdup(wind_rose[1]);
		else if (strncmp(wind_rose[0], "SO", 3) == 0)
			map->so = strdup(wind_rose[1]);
		else if (strncmp(wind_rose[0], "WE", 3) == 0)
			map->we = strdup(wind_rose[1]);
		else if (strncmp(wind_rose[0], "EA", 3) == 0)
			map->ea = strdup(wind_rose[1]);
		free_tab(wind_rose);
		i++;
	}
	printf("%s\n%s\n%s\n%s\n", map->no, map->so, map->we, map->ea);
}
