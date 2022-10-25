/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_width_height.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:33:25 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/24 22:56:06 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void resize_width_height(t_data *data)
{
	int height_backup;

	data->mlx_ptr_size = NULL;
	data->mlx_ptr_size = mlx_init(); // protect
	mlx_get_screen_size(data->mlx_ptr_size, &data->width, &data->height);
	if (data->width < WIDTH || data->height < HEIGHT)
	{
		height_backup = data->height;
		while (data->height >= height_backup)
		{
			data->width = data->width * 3 / 4;
			data->height = data->width * HEIGHT / WIDTH;
		}
	}
	else
	{
		data->width = WIDTH;
		data->height = HEIGHT;
	}
}





