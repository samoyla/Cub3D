/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:16 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/06 16:41:46 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
		
	init_map(&map);	
	if (ac != 2)
		ft_exit();
	if (if_dir(av[1]) == FAILURE)
	{
		printf("It's a dirtectory");
	 	exit(FAILURE);        		
	}
	if (if_file_exists(av[1]) == FAILURE)
	{
		printf("File does not exist\n");
		exit(FAILURE);
	}
	if (check_ext(av[1]) == FAILURE)
	{
		printf("wrong file extension\n");
		exit(FAILURE);
	}
	tab_from_map(av[1], &map);
	second_parse(&map);
	init_data(&data, "Cub3D");
	init_image(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, &ft_red_cross, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
	ft_free_n_destroy(&data);
}
