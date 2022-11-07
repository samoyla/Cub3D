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
	while (str && str[i])
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
	int	end_of_whole;

	i = -1;
	j = 0;
	map->decor = ft_calloc(6 + 1, sizeof(char *));
	if (map->decor == NULL)
		return ;
	while (map-> whole && map->whole[++i])
	{
		if (check_line_space(map->whole[i]) == SUCCESS)
		{
			if (j <= 5)
			{
				map->decor[j] = ft_strdup(map->whole[i]);
				j++;
				//printf("i=%d---j=%d\n", i, j);
			}
			else
			{
				map->index = i;
				break ;
			}		
		}
	}
	//printf("index = %d\n", map->index);
	end_of_whole = map->size;
	//printf("end of map = %d\n", end_of_whole);
	while (map->whole[map->index])
	{
		while(check_line_space(map->whole[map->index]) == FAILURE)
			map->index++;
		break ;
		//printf("index debut map =  %d\n", map->index);
		map->index++;
	}
	map->count = end_of_whole - map->index;
	//printf("size of map to calloc is = %d\n", map->count);
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

int	tab_map(char *pathname, t_map *map)
{
	int	i;
	int	j;
	int	size_max;

	i = 0;
	j = map->index;
	if (j == 0)
		return (FAILURE);
	size_max = max_width(&map->whole[j], map);
	map->map = ft_calloc(map->count + 1, sizeof(char *));
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
