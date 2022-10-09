/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/09 12:19:39 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*init_data(t_data *data, char *name)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		free(data->mlx_ptr);
		ft_error();
	}
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, name);
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		free(data->mlx_ptr);
		ft_error();
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

void	init_map(t_map *map)
{	
	map->whole = NULL;
	map->map = NULL;
	map->tx = NULL;
	map->ret = 0;
	map->so = NULL;
	map->no = NULL;
	map->ea = NULL;
	map->we = NULL;
}
