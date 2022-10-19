/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_division.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:27:24 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/19 13:39:32 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_texture(t_map *map)
{
	int		i;
	char	**wind_rose;

	i = -1;
	while (map->decor[++i] && i < 6)
	{
		wind_rose = ft_split(map->decor[i], ' ');
		if (ft_strncmp(wind_rose[0], "NO", 2) == 0)
			map->no = ft_strdup(wind_rose[1]);
		else if (ft_strncmp(wind_rose[0], "SO", 2) == 0)
			map->so = ft_strdup(wind_rose[1]);
		else if (ft_strncmp(wind_rose[0], "WE", 2) == 0)
			map->we = ft_strdup(wind_rose[1]);
		else if (ft_strncmp(wind_rose[0], "EA", 2) == 0)
			map->ea = ft_strdup(wind_rose[1]);
		free_tab(wind_rose);
	}
	printf("%s\n%s\n%s\n%s\n", map->no, map->so, map->we, map->ea);
}

void	get_color(t_map *map)
{
	int		i;
	char	**color_line;
	char	**rgb;

	i = -1;
	while (map->decor[++i] && i < 6)
	{
		color_line = ft_split(map->decor[i], ' ');
		if (ft_strncmp(color_line[0], "F", 2) == 0)
		{
			rgb = ft_split(color_line[1], ',');
			map->f_red = ft_atoi(rgb[0]);
			map->f_green = ft_atoi(rgb[1]);
			map->f_blue = ft_atoi(rgb[2]);
			free_tab(rgb);
		}
		if (ft_strncmp(color_line[0], "C", 2) == 0)
		{
			rgb = ft_split(color_line[1], ',');
			map->c_red = ft_atoi(rgb[0]);
			map->c_green = ft_atoi(rgb[1]);
			map->c_blue = ft_atoi(rgb[2]);
			free_tab(rgb);
		}
	}
	printf("-----------------------\n");
	printf("f_r = %d\nf_g = %d\nf_b = %d\n", map->f_red, map->f_green, map->f_blue);
	printf("-----------------------\n");
	printf("c_r = %d\nc_g = %d\nc_b = %d\n", map->c_red, map->c_green, map->c_blue);
}

