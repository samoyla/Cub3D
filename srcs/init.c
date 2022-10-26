/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:07:48 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/26 21:16:59 by iguscett         ###   ########.fr       */
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
	data->tex.no.img = NULL;
	data->tex.so.img = NULL;
	data->tex.ea.img = NULL;
	data->tex.we.img = NULL;
	data->tex.no.addr = NULL;
	data->tex.so.addr = NULL;
	data->tex.ea.addr = NULL;
	data->tex.we.addr = NULL;
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

	printf("T:|%s|\n", path);
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
