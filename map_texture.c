/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:41:37 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 14:08:18 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_texture(t_map *map)
{
	int		i;
	char	**wind_rose;

	i = 0;
	wind_rose = NULL;
	while (map->decor[i] && i < 6)
	{
		if (if_not_spaces(map->decor[i]) == SUCCESS)
		{
			map->decor[i] = ft_strtrim(map->decor[i], " ");
			printf("trim = %s\n", map->decor[i]);
			wind_rose = ft_split(map->decor[i], ' ');
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
		else
		{
			//printf("Error\n");
			//printf("lines contain more than spaces\n");
			return (FAILURE);
		}
	}
	printf("%s\n%s\n%s\n%s\n", map->no, map->so, map->we, map->ea);
	return (SUCCESS);
}
