/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/20 17:59:11 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (FAILURE);
	while (str[i])
	{
		if (str[i] > 32)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

void	tab_decor(char *pathname, t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = -1;
	count = 0;
	map->decor = ft_calloc(6 + 1, sizeof(char *));
	if (map->decor == NULL)
		return ;
	while (map->whole[i])
	{
		if (check_line_space(map->whole[i]) == SUCCESS)
		{
			if (++j <= 5)
				map->decor[j] = ft_strdup(map->whole[i]);
		}
		else
			count++;
		i++;

	}
	map->count = count;
	printf("map-count = %d\n", map->count);
	//print_tab(map->decor);//supprimer
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 32)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	real_size_map(t_map *map)
{
	int	i;

	i = 0;
	while(map->whole)
	{
		
	}
}

int	tab_map(char *pathname, t_map *map)
{
	int	i;
	int	j;
	int	size;
	int	size_max;

	i = 0;
	j = 6 + map->count;
	size = map->size - j;
	printf("size of map is %d\n", size);
	if (size == 0)
		return (FAILURE);
	size_max = max_width(&map->whole[j], map);
	map->map = ft_calloc(size, sizeof(char *));
	if (!map->map)
		return (FAILURE);
	while (map->whole[j] != NULL)
	{
		map->map[i] = ft_strdup_space(map->whole[j], size_max);
			i++;
		j++;
	}
	printf("--------------------------------------------------\n");
	print_tab(map->map);
	printf("--------------------------------------------------\n");
	return (SUCCESS);
}
