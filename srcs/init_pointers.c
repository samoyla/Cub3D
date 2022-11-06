/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:52:45 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_pointers_map(t_data *data)
{
	data->map.whole = NULL;
	data->map.decor = NULL;
	data->map.map = NULL;
	data->map.input = NULL;
	data->map.no = NULL;
	data->map.ea = NULL;
	data->map.so = NULL;
	data->map.we = NULL;
}

void init_pointers_screen_img(t_data *data)
{
	data->img.addr = NULL;
	data->img.iaddr = NULL;
	data->img.img = NULL;
}

void init_pointers_wall(t_data *data)
{
	data->wall.wheight = NULL;
	data->wall.col = NULL;
	data->wall.side = NULL;
}

void init_pointers_textures(t_data *data)
{
	data->tex.no.addr = NULL;
	data->tex.no.iaddr = NULL;
	data->tex.no.img = NULL;
	data->tex.ea.addr = NULL;
	data->tex.ea.iaddr = NULL;
	data->tex.ea.img = NULL;
	data->tex.so.addr = NULL;
	data->tex.so.iaddr = NULL;
	data->tex.so.img = NULL;
	data->tex.we.addr = NULL;
	data->tex.we.iaddr = NULL;
	data->tex.we.img = NULL;
}

void	init_pointers(t_data *data)
{
	data->mlx_ptr_size = NULL;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	init_pointers_map(data);
	init_pointers_screen_img(data);
	data->player.angles = NULL;
	init_pointers_wall(data);
	init_pointers_textures(data);
}
