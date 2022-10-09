/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 18:54:54 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/09 15:37:51 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


char	*s_n_r(char *str, char c, char ac)
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

int	map_size(char *pathname)
{
	int		i;
	char	*line;
	int		fd;

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

void	tab_whole_map(char *pathname, t_map *map)
{
	int		fd;
	int		i;
	int		size;
	char	*line;

	i = 0;
	fd = open(pathname, O_RDONLY);
	line = get_next_line(fd);
	size = map_size(pathname);
	printf("whole map size = %d\n", size);
	map->whole = calloc(size +1, sizeof(char *));
	while (i < size)
	{
		s_n_r(line, '\n', '\0');
		map->whole[i] = strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	map->whole[i] = 0;
	free(line);
}
