/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:54:54 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/06 18:43:07 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static char	*s_n_r(char *str, char c, char ac)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] == c)
			str[i] = ac;
		i++; 
	}
	return (str);
}

static int	map_size(char *pathname)
{
	int	i;
	char	*line;
	int	fd;
	
	i = 0; 
	line = NULL;
	fd = open(pathname, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (0);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	free(line);
	return (i);
}

void	tab_from_map(char *pathname, t_map *map)
{
	int	fd;
	int	i;
	int	size;
	char	*line;
		
	i = 0;
	fd = open(pathname, O_RDONLY);
	line = get_next_line(fd);
	size = map_size(pathname);
	map->wmap = malloc(sizeof(char*) * size + 1);
	while (i < size)
	{
		s_n_r(line, '\n', '\0');
		map->wmap[i] = strdup(line);
		//printf("%s\n", map->wmap[i]);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	map->wmap[i] = 0;
	free(line);
}
