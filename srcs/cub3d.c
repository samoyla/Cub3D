/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:03:16 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/18 14:31:51 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map;
	t_check	check;

	init_map(&map);
	init_check(&check);
	if (check_args(ac) == FAILURE)
		return (FAILURE);
	if (check_file(av[1]) == FAILURE)
		return (FAILURE);
	if (create_tab_elements(av[1], &map, &check) == FAILURE)
		return (FAILURE);
	get_texture(&map);
	get_color(&map);


//---------------------------------------------------------------------
//mlx part
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
