/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/14 16:41:10 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line_space(char *str)
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

void	tab_texture(char *pathname, t_map *map)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(pathname, O_RDONLY);
	check_fd(fd);
	line = get_next_line(fd);
	map->decor = calloc(6 + 1, sizeof(char *));
	if (map->decor == NULL)
		return ;
	while (line != NULL)
	{
		if (check_line_space(line) == SUCCESS)
		{
			if (i <= 5)
			{	
				s_n_r(line, '\n', '\0');
				map->decor[i] = strdup(line);
				i++;
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	print_tab(map->decor);//supprimer
	free(line);
	close(fd);
}

int	if_not_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 32)
			return (SUCCESS);
		else
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	size_void(char *pathname)
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

void	tab_map(char *pathname, t_map *map)
{
	int	i;
	int	j;
	int	a;
	int	size;

	i = 0;
	a = map_size(pathname);
	j = size_void(pathname);
	printf("a = %d\nj = %d\n", a, j);
	size = a - j;
	printf("size of map = %d\n", size);
	map->map = ft_calloc(size + 1, sizeof(char *));
	if (!map->map)
		return ;
	while (map->whole[j] != NULL)
	{
		if (strchr(map->whole[j], '1') || strchr(map->whole[j], '0')
			|| strchr(map->whole[j], 'N') || strchr(map->whole[j], 'S')
			||strchr(map->whole[j], 'W') || strchr(map->whole[j], 'E'))
		{
			map->map[i] = ft_strdup(map->whole[j]);
			i++;
		}
		j++;
	}
	map->map[i] = 0;
	print_tab(map->map);//supprimer
}
