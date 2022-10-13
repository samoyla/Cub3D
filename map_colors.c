/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:22:06 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 17:27:27 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_color(t_map *map)
{
	int		i;
	char	**color_line;
	char	**rgb;

	i = 0;
	color_line = NULL;
	rgb = NULL;
	while (map->decor[i] && i < 6)
	{
		map->decor[i] = ft_strtrim(map->decor[i], " ");
		color_line = ft_split(map->decor[i], ' ');
		if (strncmp(color_line[0], "F", 2) == 0)
		{
			rgb = ft_split(color_line[1], ',');
			map->f_red = atoi(rgb[0]);
			map->f_green = atoi(rgb[1]);
			map->f_blue = atoi(rgb[2]);
			free_tab(rgb);
		}
		else if (strncmp(color_line[0], "C", 2) == 0)
		{
			rgb = ft_split(color_line[1], ',');
			map->c_red = atoi(rgb[0]);
			map->c_green = atoi(rgb[1]);
			map->c_blue = atoi(rgb[2]);
			free_tab(rgb);
		}
		i++;
	}
	printf("-----------------------\n");
	printf("f_r = %d\nf_g = %d\nf_b = %d\n", map->f_red, map->f_green, map->f_blue);
	printf("-----------------------\n");
	printf("c_r = %d\nc_g = %d\nc_b = %d\n", map->c_red, map->c_green, map->c_blue);
}

