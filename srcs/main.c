/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:16 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 11:15:24 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// check ALL MALLOCS
// check map file, redo extensin checker
//

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	t_check	check;

	init_pointers(&data);
	if (!(*env))
		exit_free_destroy(&data, "env doesn't exist\n", FAILURE);
	init_map_and_check_struct(&data, &check);
	check_nb_args_and_file(&data, argc, argv);
	get_and_analyze_map(&data, &check, argv);
	get_map(&data);
	init_player(&data);
	init_screen_and_hud(&data);
	get_wall_height(&data);
	init_data_image_textures(&data, "Cub3D");
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 0L, &ft_red_cross, &data);
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
	exit_free_destroy(&data, NULL, SUCCESS);
	return (SUCCESS);
}
