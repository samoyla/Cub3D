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
	while (str && str[i])
	{
		while (str[i] == c)
			str[i] = ac;
		i++;
	}
	return (str);
}

static int	ft_whitespaces_no_n(char c)
{
	if (c == ' ' || c == '\r'
		|| c == '\t' || c == '\v' || c == '\f')
		return (SUCCESS);
	return (FAILURE);
}

static int	check_input(char *str)
{
	int	i;
	int	flag_start;
	int end;

	i = 0;
	flag_start = 0;
	while (*str)
	{
		while (*str && *str != '\n')
		{
			while (*str && !ft_whitespaces_no_n(*str))
				str++;
			if (*str == '1')
			{
				flag_start = 1;
				break;
			}
			else
				break;
		}
		if (flag_start)
			break;
		while (*str && *str != '\n')
			str++;
		if (*str != '\0')
			str++;
	}
	while (*str)
	{
		if (*str == '\n' && *(str + 1) && *(str + 1) == '\n')
		{
		 	printf("Error\nempty horizontal lines in map\n");
		 	exit (FAILURE);
		 }
		 else
		 	str++;
	}
	return (SUCCESS);
}

void	tab_whole_map(t_map *map, char **av)
{
	int		i;

	i = 0;
	read_input(map, av);
	if (check_input(map->input) == FAILURE)
		exit (FAILURE);
	map->whole = ft_split(map->input, '\n');
	while (map->whole[i])
		i++;
	map->size = i;
	printf("size of whole map = %d\n", map->size);
	print_tab(map->whole);
	free(map->input);
}
