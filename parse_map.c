/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/06 18:45:04 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_height(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 0;
	while(map->wmap[j] != NULL)
	{
		i = 0;
		while(map->wmap[j][i] != '\0')
		{
			if (map->wmap[j][i] == '1' || map->wmap[j][i] == '0' || map->wmap[j][i] == 'N'
				|| map->wmap[j][i] == 'S' || map->wmap[j][i] == 'W' || map->wmap[j][i] == 'E')
			{	
				count++;	
				break;
			}
			else
				i++;
		}
		j++;
	}
	return (count);
}

void	print_tab(char	**tab)
{
	int	i;
	
	i = 0;
	while (tab[i])
	{
		printf("tab[%d]%s\n", i, tab[i]);
		i++;
	}
}

void	second_parse(t_map *map)
{
	int	i;
	int	j;
	int	size;


	j = 0;
	i = 0;
	size = map_height(map);
	map->smap = malloc(sizeof(char**) * size + 1);
	while(map->wmap[j] != NULL)
	{
		if (strchr(map->wmap[j], '1') || strchr(map->wmap[j], '0')
			|| strchr(map->wmap[j], 'N') ||strchr(map->wmap[j], 'S')
			||strchr(map->wmap[j], 'W') || strchr(map->wmap[j], 'E'))
		{
			map->smap[i] = strdup(map->wmap[j]);
			i++;
		}
		j++;
	}
	map->smap[i] = 0;
	print_tab(map->smap);
}
