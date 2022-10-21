/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 16:00:08 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/20 18:27:30 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keysym, t_data *data, t_map *map)
{
	if (keysym == XK_Escape)
	{
		ft_red_cross(data, map);
	}
	return (0);
}

int	ft_red_cross(t_data *data, t_map *map)
{
	ft_free_n_destroy(data);
	//free_tab(map->decor);
	//free_tab(map->whole);
	exit (0);
}
