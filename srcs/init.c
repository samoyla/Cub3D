/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/30 17:31:59 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map(t_map *map)
{
	get_texture(map);
	get_color(map);
}

t_data	*init_data(t_data *data, char *name)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		free(data->mlx_ptr);
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
	data->img.img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT); // adapt here to real case!!
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.iaddr = (int *)mlx_get_data_addr(data->img.img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.x = (double)data->width;
	data->img.y = (double)data->height;
	return (data);
}



void load_textures(t_data *data, t_img *img, char *path)
{
	int x;
	int y;

	printf("\nT:|%s|\n", path);
	img->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &x, &y);
	if (img->img == NULL)
		printf("IMG ERROR\n"); // proteger, free and exit
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	img->iaddr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (img->addr == NULL)
		printf("ADDR ERROR\n"); // proteger, free and exit
	printf("T:|%s| x:%d y:%d p:%p\n", path, x, y, img);
	img->x = (double)x;
	img->y = (double)y;
	printf("ll:%d x:%f y:%f\n", img->line_len, img->x, img->y);

	// verify_size_of_texture(img);
	int i = 0;
	// while (img->iaddr[i])
	// 	i++;

}

void init_textures(t_data *data)
{
	printf("\n\n");
	load_textures(data, &data->tex.no, data->map.no);
	load_textures(data, &data->tex.so, data->map.so);
	load_textures(data, &data->tex.we, data->map.we);
	load_textures(data, &data->tex.ea, data->map.ea);
	data->wall.texture = malloc(sizeof(t_img)); // protect malloc
}
