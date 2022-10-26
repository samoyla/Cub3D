/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:16 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/25 11:55:31 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	//t_map	map;
	t_check	check;

	if (!(*env))
	{
		ft_putstr_fd("env doesn't exist\n", 2);
		exit(FAILURE);
	}
	init_map(&data.map);
	init_check(&check);
	if (check_args(ac) == FAILURE)
		exit (FAILURE);
	if (check_file(av[1]) == FAILURE)
		exit (FAILURE);
	if (create_tab_elements(av[1], &data.map, &check, av) == FAILURE)
		exit (FAILURE);
	get_map(&data.map);
	
// 	printf("floor color:%d ceilling:%d\n", data.map.floor, data.map.ceilling);
// // PRINT MAP
// 	int i = -1;
// 	while (data.map.map[++i])
// 		printf("|%s|\n", data.map.map[i]);
// 	printf("pi:%f and FOV:%f\n", PI, FOV);
// 	get_map_size(&data.map);

// // INIT PLAYER
// 	init_player(&data);

// // MLX
// 	resize_width_height(&data);
// 	printf("width:%d\n", data.width);
// 	data.screen.dist = malloc(sizeof(data.screen.dist) *(data.width + 1)); // protect malloc
// 	data.screen.dist[data.width] = -1;
// 	data.screen.wheight = malloc(sizeof(data.screen.wheight) *(data.width + 1)); // protect malloc
// 	data.screen.wheight[data.width] = -1;
// 	printf("map ysize:%ld and xsize:%ld\n", data.map.ysize, data.map.xsize);
// 	set_screen_points(&data);
// 	set_hud(&data);
// 	wall_distance(&data);

// 	init_data(&data, "Cub3D");
// 	init_image(&data);
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
// 	mlx_hook(data.win_ptr, 17, 0L, &ft_red_cross, &data);
// 	mlx_loop_hook(data.mlx_ptr, &render, &data);
// 	mlx_loop(data.mlx_ptr);
// 	free(data.mlx_ptr);
// 	ft_free_n_destroy(&data);
	free_map_struct(&data.map);
	return (SUCCESS);
}
