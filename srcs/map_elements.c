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
	j = 0;
	count = 0;
	map->decor = ft_calloc(6 + 1, sizeof(char *));
	if (map->decor == NULL)
		return ;	
	while (map->whole[i])
	{
		if (check_line_space(map->whole[i]) == SUCCESS)
		{
			if (j <= 5)
			{	
				map->decor[j] = ft_strdup(map->whole[i]);
				j++;
			}
		}
		i++;
	}
	print_tab(map->decor);//supprimer
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

static int	size_till_map(char *pathname)
{
	int		count;
	int		fd;
	int		i;
	char	*line;

	count = 0;
	i = 0;
	fd = open(pathname, O_RDONLY);
	check_fd(fd);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (check_line_space(line) == SUCCESS)
		{
			if (i <= 5)
				i++;
		}
		else
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (i + count);
}

int	tab_map(char *pathname, t_map *map)
{
	int	i;
	int	j;
	int	a;
	int	size;
	int	size_max;

	i = 0;
	a = map_size(pathname);
	j = size_till_map(pathname);
	size = a - j;
	if (size == 0)
		return (FAILURE);
	size_max = max_width(&map->whole[j]);
	map->map = ft_calloc(size + 1, sizeof(char *));
	if (!map->map)
		return (FAILURE);
	while (map->whole[j] != NULL)
	{
		if (ft_strchr(map->whole[j], '1') || ft_strchr(map->whole[j], '0')
			|| ft_strchr(map->whole[j], 'N') || ft_strchr(map->whole[j], 'S')
			|| ft_strchr(map->whole[j], 'W') || ft_strchr(map->whole[j], 'E'))
		{
			map->map[i] = ft_strdup_space(map->whole[j], size_max);
			i++;
		}
		j++;
	}
	map->map[i] = 0;
	print_tab(map->map);//supprimer
	return (SUCCESS);
}
