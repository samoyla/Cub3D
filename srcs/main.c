/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:16 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/30 18:10:12 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	OK Passer a travers le mur en marche arriere
	OK map adaptable abandonne
	OK proteger xpm abandonne
	- restructurer le tout et cleaner
	- protege mallocs
	- leaks

	!! une map vide segfault!!!
*/

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_check	check;

	init_pointers(&data);
	if (!(*env))
		err_free_ptrs(&data, "env doesn't exist\n");
	init_map_and_check_struct(&data, &check);
	check_nb_args_and_file(&data, argc, argv);
	if (create_tab_elements(argv[1], &data.map, &check, argv) == FAILURE)
		;
		// exit (FAILURE);
	get_map(&data.map);
//---------------------------------------------------------------------
	get_map_size(&data.map);
// // INIT PLAYER
	init_player(&data);

// // MLX
	resize_width_height(&data);
	init_screen(&data);
	set_hud(&data);
	get_wall_height(&data);
	init_data(&data, "Cub3D");
	init_image(&data);
	init_textures(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, &ft_red_cross, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	free(data.mlx_ptr);
	ft_free_n_destroy(&data);

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
