/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/06 18:45:04 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_line_tx(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 32)
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	tab_texture(char *pathname, t_map *map)
{
	int		count;
	int		fd;
	int		i;
	int		j;

	count = 0;
	i = 0;
	j = 0;
	fd = open(pathname, O_RDONLY);
	if (fd < 0)
		ft_error();
	map->tx = malloc(sizeof(char *) * 6 + 1);
	while (map->whole[j] != NULL)
	{
		if (check_line_tx(map->whole[j]) == SUCCESS)
		{
			if (i <= 5)
			{	
				map->tx[j] = strdup(map->whole[j]);
				//printf("%s\n", map->tx[j]);
				i++;
			}
		}
		else
			count++;
		j++;
	}
	close(fd);
	map->ret = i + count;
	printf("%d\n", map->ret);
	return (map->ret);
}

/*static int	map_height(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (map->whole[j] != NULL)
	{
		i = 0;
		while (map->whole[j][i] != '\0')
		{
			if (map->whole[j][i] == '1' || map->whole[j][i] == '0'
				|| map->whole[j][i] == 'N' || map->whole[j][i] == 'S'
				|| map->whole[j][i] == 'W' || map->whole[j][i] == 'E')
			{	
				count++;
				break ;
			}
			else
				i++;
		}
		j++;
	}
	return (count);
}*/

void	tab_map(t_map *map, char *pathname)
{
	int	i;
	int	j;
	int	a;
	int	size;

	i = 0;
	j = map->ret;
	a = map_size(pathname);
	size = a - map->ret;
	printf("size = %d\n", size);
	map->map = malloc(sizeof(char **) * size + 1);
	while (map->whole[j] != NULL)
	{
		if (strchr(map->whole[j], '1') || strchr(map->whole[j], '0')
			|| strchr(map->whole[j], 'N') || strchr(map->whole[j], 'S')
			||strchr(map->whole[j], 'W') || strchr(map->whole[j], 'E'))
		{
			map->map[i] = strdup(map->whole[j]);
			i++;
		}
		j++;
	}
	map->map[i] = 0;
	print_tab(map->map);
}
