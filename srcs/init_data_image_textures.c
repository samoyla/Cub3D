/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_image_textures.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 11:04:40 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_image(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, data->width, data->height);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.iaddr = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	if (data->img.addr == NULL || data->img.iaddr == NULL)
		exit_free_destroy(data, "Problem loading image adress\n", FAILURE);
	data->img.x = (double)data->width;
	data->img.y = (double)data->height;
}

void	load_textures(t_data *data, t_img *img, char *path)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &x, &y);
	if (img->img == NULL)
		exit_free_destroy(data, "Problem loading image\n", FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp,
			&img->line_len, &img->endian);
	img->iaddr = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->line_len, &img->endian);
	if (img->addr == NULL || img->iaddr == NULL)
		exit_free_destroy(data, "Problem loading image adress\n", FAILURE);
	img->x = (double)x;
	img->y = (double)y;
}

void	init_textures(t_data *data)
{
	load_textures(data, &data->tex.no, data->map.no);
	load_textures(data, &data->tex.so, data->map.so);
	load_textures(data, &data->tex.we, data->map.we);
	load_textures(data, &data->tex.ea, data->map.ea);
}

void	init_data_image_textures(t_data *data, char *name)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		exit_free_destroy(data, "Problem initialazing mlx\n", FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->width, data->height, name);
	if (data->win_ptr == NULL)
		exit_free_destroy(data, "Problem initialazing mlx\n", FAILURE);
	init_image(data);
	init_textures(data);
}
