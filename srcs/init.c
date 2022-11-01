/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/22 11:25:07 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Map
void	init_map(t_map *map)
{
	map->whole = NULL;
	map->decor = NULL;
	map->map = NULL;
	map->input = NULL;
	map->so = NULL;
	map->no = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->size = 0;
	map->count = 0;
	map->f_red = 0;
	map->f_green = 0;
	map->f_blue = 0;
	map->c_red = 0;
	map->c_green = 0;
	map->c_blue = 0;
	map->index = 0;
}

void	init_check(t_check *check)
{
	check->f = 0;
	check->c = 0;
	check->no = 0;
	check->so = 0;
	check->we = 0;
	check->ea = 0;
}

void	get_map(t_map *map)
{
	get_texture(map);
	get_color(map);
}

//MLX
t_data	*init_data(t_data *data, char *name)
{
	data->mlx_ptr = NULL;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		free(data->mlx_ptr);
	data->win_ptr = NULL;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width, data->height, name);
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		free(data->mlx_ptr);
	}
	return (data);
}

t_data	*init_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (data);
}
