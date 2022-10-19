/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:32:36 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/19 16:42:31 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	create_tab_elements(char *pathname, t_map *map, t_check *check)
{
	tab_whole_map(pathname, map);
	tab_decor(pathname, map);
	if (decor_analysis(map, check) == FAILURE)
		return (FAILURE);
	if (tab_map(pathname, map) == FAILURE)
	{
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
		line = get_next_line(fd);
		free(line);
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
	if (!map->whole)
		return ;
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
