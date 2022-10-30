/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:29:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/30 17:14:23 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_n_destroy(t_data *data)
{
	if (data->win_ptr && data->mlx_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (data->img.img && data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		data->img.img = NULL;
	}
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		data->mlx_ptr = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_map_struct(t_map *map)
{
	if (map == NULL)
		return ;
	if (map->whole)
		free_tab(map->whole);
	if (map->decor)
		free_tab(map->decor);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
	free(map);
}

void free_pointers_map(t_data *data)
{
	if (data->map.whole)
		free(data->map.whole);
	if (data->map.whole)
		free(data->map.decor);
	if (data->map.map)
		free(data->map.map); // char **
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
}

void free_pointers_screen_img(t_data *data)
{
	if (data->img.addr)
		free(data->img.addr);
	if (data->img.iaddr)
		free(data->img.iaddr);
	if (data->img.img)
		free(data->img.img);
}

void free_pointers_wall(t_data *data)
{
	if (data->wall.texture)
		free(data->wall.texture);
	if (data->wall.wheight)
		free(data->wall.wheight);
	if (data->wall.col)
		free(data->wall.col);
	if (data->wall.side)
		free(data->wall.side);
}

void free_pointers_textures(t_data *data)
{
	if (data->tex.no.addr)
		free(data->tex.no.addr);
	if (data->tex.no.iaddr)
		free(data->tex.no.iaddr);
	if (data->tex.no.img)
		free(data->tex.no.img);
	if (data->tex.ea.addr)
		free(data->tex.ea.addr);
	if (data->tex.ea.iaddr)
		free(data->tex.ea.iaddr);
	if (data->tex.ea.img)
		free(data->tex.ea.img);
	if (data->tex.so.addr)
		free(data->tex.so.addr);
	if (data->tex.so.iaddr)
		free(data->tex.so.iaddr);
	if (data->tex.so.img)
		free(data->tex.so.img);
	if (data->tex.we.addr)
		free(data->tex.we.addr);
	if (data->tex.we.iaddr)
		free(data->tex.we.iaddr);
	if (data->tex.we.img)
		free(data->tex.we.img);
}

void err_free_ptrs(t_data *data, char *err)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(err, 2);
	if (data->mlx_ptr_size)
		free(data->mlx_ptr_size);
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	if (data->win_ptr)
		free(data->win_ptr);
	free_pointers_map(data);
	free_pointers_screen_img(data);
	if (data->player.angles)
		free(data->player.angles);
	free_pointers_wall(data);
	free_pointers_textures(data);
	exit (FAILURE);
}
