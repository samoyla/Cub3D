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

int	tab_map(char *pathname, t_map *map)
{
	int	i;
	int	j;
	int	size;
	int	size_max;

	i = 0;
	j = map->count + 6;
	printf("j = %d\n", j);
	size = map->size - map->count + 6;
	if (size == 0)
		return (FAILURE);
	size_max = max_width(&map->whole[j], map);
	map->map = ft_calloc(size + 1, sizeof(char *));
	if (!map->map)
		return (FAILURE);
	while (map->whole[j] != NULL)
	{
		map->map[i] = ft_strdup_space(map->whole[j], size_max);
			i++;
		j++;
	}
	map->map[i] = 0;
	return (SUCCESS);
}
