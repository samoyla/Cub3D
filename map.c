/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:44:54 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/17 10:43:15 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_analysis(t_map *map)
{
	if (forbidden_map_ch(map) == FAILURE)
		return (FAILURE);
	else if (check_player(map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_all_walls(t_map *map, int i, int j)
{
	if (i == 0 || map->map[i + 1] == NULL)
		return (FAILURE);
	if (j == 0 || map->map[i][j + 1] == '\0')
		return (FAILURE);
	else if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' '
			|| map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
		return (FAILURE);
	return (SUCCESS);
}

int	forbidden_map_ch(t_map *map)
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

int	check_player(t_map *map)
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
		ft_putstr_fd("Error\nwrong number of players\n", 2);
		return (FAILURE);
	}
	if (nb_p == 1)
		if (check_if_inside(map) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

int	check_if_inside(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = 0;
		while (map->map[i][++j])
		{
			if ((map->map[i][j] == '0' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
				&& check_all_walls(map, i, j) == FAILURE)
			{
				ft_putstr_fd("Error\nwrong player position\n", 2);
				return (FAILURE);
			}
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' ||  map->map[i][j] == 'E')
				printf("init player position\n");
		}
	}
	return (SUCCESS);
}
