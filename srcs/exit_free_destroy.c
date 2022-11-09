/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:29:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 16:19:43 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mlx_free_and_destroy(t_data *data)
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

void	destroy_textures(t_data *data)
{
	if (data->tex.no.img && data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->tex.no.img);
		data->tex.no.img = NULL;
	}
	if (data->tex.ea.img && data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->tex.ea.img);
		data->tex.ea.img = NULL;
	}
	if (data->tex.so.img && data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->tex.so.img);
		data->tex.so.img = NULL;
	}
	if (data->tex.we.img && data->mlx_ptr)
	{
		mlx_destroy_image(data->mlx_ptr, data->tex.we.img);
		data->tex.we.img = NULL;
	}
}

void	exit_free_destroy(t_data *data, char *err, int exit_code)
{
	if (exit_code == FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd(err, 2);
	}
	free_pointers_map(data);
	if (data->player.angles)
		free(data->player.angles);
	free_pointers_wall(data);
	destroy_textures(data);
	mlx_free_and_destroy(data);
	exit (exit_code);
}
