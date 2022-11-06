/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:44:54 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:57:56 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	forbidden_map_ch(t_map *map)
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
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int check_in_walls(t_map *map, int i, int j)
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

static int	check_if_inside(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if ((map->map[i][j] == '0'
				|| map->map[i][j] == 'N'
				|| map->map[i][j] == 'E'
				|| map->map[i][j] == 'S'
				|| map->map[i][j] == 'W')
				&& check_in_walls(map, i, j) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}

static void check_player(t_data *data)
{
	int	i;
	int	j;
	int	nb_p;

	i = -1;
	nb_p = 0;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			if (data->map.map[i][j] == 'N'
				|| data->map.map[i][j] == 'E'
				|| data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'W')
				nb_p++;
		}
	}
	if (nb_p != 1)
		exit_free_destroy(data, "Two or more players on map\n", FAILURE);
	if (nb_p == 1 && (check_if_inside(&data->map) == FAILURE))
		exit_free_destroy(data, "Wrong player position or map is open\n", FAILURE);
}

void map_analysis(t_data *data)
{
	if (forbidden_map_ch(&data->map) == FAILURE)
		exit_free_destroy(data, "Wrong character(s) in map\n", FAILURE);
	check_player(data);
}
