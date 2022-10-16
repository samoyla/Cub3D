/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:32:36 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/14 15:42:39 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_tab_elements(char *pathname, t_map *map)
{
	tab_whole_map(pathname, map);
	tab_texture(pathname, map);
	tab_map(pathname, map);
}

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
	fd = open(pathname, O_RDONLY);
	check_fd(fd);
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
	check_fd(fd);
	line = get_next_line(fd);
	size = map_size(pathname);
	map->whole = ft_calloc(size + 1, sizeof(char *));
	while (i < size)
	{
		s_n_r(line, '\n', '\0');
		map->whole[i] = ft_strdup(line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	map->whole[i] = 0;
	free(line);
}
