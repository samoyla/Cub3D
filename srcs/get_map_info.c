/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:32:36 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/22 13:36:01 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_tab_elements(char *pathname, t_map *map, t_check *check, char **av)
{
	tab_whole_map(map, av);
	tab_decor(pathname, map);
	if (decor_analysis(map, check) == FAILURE)
	{
		//free_map_struct(map);
		return (FAILURE);
	}
	if (tab_map(pathname, map) == FAILURE)
	{
		//free_map_struct(map);
		ft_putstr_fd("Error\nmap doesn't exist\n", 2);
		return (FAILURE);
	}
	if (map_analysis(map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

char	*s_n_r(char *str, char c, char ac)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		while (str[i] == c)
			str[i] = ac;
		i++;
	}
	return (str);
}

void	tab_whole_map(t_map *map, char **av)
{
	int		i;

	i = 0;
	read_input(map, av);
	map->whole = ft_split(map->input, '\n');
	while (map->whole[i])
		i++;
	map->size = i;
	printf("size of whole map = %d\n", map->size);
	free(map->input);
}
