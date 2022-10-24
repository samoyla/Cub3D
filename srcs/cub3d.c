/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:16 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/24 16:29:24 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_check	check;

	init_map(&data.map);
	init_check(&check);
	if (check_args(ac) == FAILURE)
		return (FAILURE);
	if (check_file(av[1]) == FAILURE)
		return (FAILURE);
	create_tab_elements(av[1], &data.map);
	if (decor_analysis(&data.map, &check) == FAILURE)
		return (FAILURE);
	// if (map_analysis(&data.map) == FAILURE)
	// 	return (FAILURE);
	get_texture(&data.map);
	get_color(&data.map);

	printf("floor color:%d ceilling:%d\n", data.map.floor, data.map.ceilling);
// PRINT MAP
	int i = -1;
	while (data.map.map[++i])
		printf("|%s|\n", data.map.map[i]);
	printf("pi:%f and FOV:%f\n", PI, FOV);
	get_map_size(&data.map);

// INIT PLAYER
	init_player(&data);

// MLX
	resize_width_height(&data);
	printf("width:%d\n", data.width);
	data.screen.dist = malloc(sizeof(data.screen.dist) *(data.width + 1)); // protect malloc
	data.screen.dist[data.width] = -1;
	data.screen.wheight = malloc(sizeof(data.screen.wheight) *(data.width + 1)); // protect malloc
	data.screen.wheight[data.width] = -1;
	printf("map ysize:%ld and xsize:%ld\n", data.map.ysize, data.map.xsize);
	set_screen_points(&data);
	set_hud(&data);
	wall_distance(&data);

	init_data(&data, "Cub3D");
	init_image(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, &ft_red_cross, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
	ft_free_n_destroy(&data);

	return (SUCCESS);
}
