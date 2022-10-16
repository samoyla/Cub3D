/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:44:54 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/16 17:22:40 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_analysis(t_map *map)
{
	if (forbidden_wall_ch(map) == FAILURE)
		return (FAILURE);
	if (check_player_nb(map) == FAILURE)
		return (FAILURE);
	//if (check_all_walls(map) == FAILURE)
	//	return (FAILURE);
	return (SUCCESS);
}

int	forbidden_wall_ch(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'W' && map->map[i][j] != 'E'
				&& map->map[i][j] != ' ')
			{
				ft_putstr_fd("forbidden characters in the map\n", 2);
				return (FAILURE);
			}
		}
	}
	return (SUCCESS);
}

int	check_player_nb(t_map *map)
{
	int	i;
	int	j;
	int	nb_p;

	i = -1;
	nb_p = 0;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
				nb_p++;
		}
	}
	if (nb_p != 1)
	{
		ft_putstr_fd("Error\nthere're several players inside\n", 2);
		return (FAILURE);
	}
	if (nb_p == 1)
		if (check_if_inside(map) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

static int check_more(t_map *map, int i, int j)
{
	if (map->map[i - 1][j] == ' ' || map->map[i + 1][j]== ' '
		|| map->map[i][j - 1] == ' ' || map->map[i][j + 1]== ' ' 
		|| map->map[i - 1][j] == '\0' || map->map[i + 1][j]== '\0')  
	{
		ft_putstr_fd("Error\nplayer is on the edge\n", 2);
		return (FAILURE);
	}
	else 
		return (SUCCESS);

}

int	check_if_inside(t_map *map)
{
	int	i;
	int	j;
	int	size;

	i = -1;
	while (map->map[++i])
	{
		j = 0;
		while (map->map[i][++j])
		{
			size = ft_strlen(map->map[i]) - 1;
			if (map->map[i][0] == 'N' || map->map[i][0] == 'S'
				|| map->map[i][0] == 'W' || map->map[i][0] == 'E')
				return (FAILURE);
			if (map->map[i][size] == 'N' || map->map[i][size] == 'S'
				|| map->map[i][size] == 'W' || map->map[i][size] == 'E')
				return (FAILURE);
			if (map->map[i][0] == 'N' || map->map[i][0] == 'S'
				|| map->map[i][0] == 'W' || map->map[i][0] == 'E')
				return (check_more(map, i, j));
		}
	}
	return (SUCCESS);
}
