/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:29:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:57:04 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_map_struct(t_map *map)
{
	if (map->whole)
		free_double_ptr_char(map->whole);
	if (map->decor)
		free_double_ptr_char(map->decor);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
}

void free_pointers_map(t_data *data)
{

	free_double_ptr_char(data->map.whole);
	free_double_ptr_char(data->map.map);
	if (data->map.input)
		free(data->map.input);
	if (data->map.no)
		free(data->map.no);
	if (data->map.ea)
		free(data->map.ea);
	if (data->map.so)
		free(data->map.so);
	if (data->map.we)
		free(data->map.we);
	free(data->map.decor);
}

void free_pointers_wall(t_data *data)
{
	if (data->wall.wheight)
		free(data->wall.wheight);
	if (data->wall.col)
		free(data->wall.col);
	if (data->wall.side)
		free(data->wall.side);
}

void exit_and_free(t_data *data, char *err, int exit_code)
{
	if (exit_code == FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(err, 2);
	}
	free_map_struct(&data->map);
	free_pointers_map(data);
	if (data->player.angles)
		free(data->player.angles);
	free_pointers_wall(data);
	exit (exit_code);
}
