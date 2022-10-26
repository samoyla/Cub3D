/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:12:05 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/25 13:16:09 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_lines(char **split, t_check *check, t_map *map)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		check->no++;
		if (check_windrose(check, split, map) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		check->so++;
		if (check_windrose(check, split, map) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		check->we++;
		if (check_windrose(check, split, map) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		check->ea++;
		if (check_windrose(check, split, map) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_color_lines(char **split, t_check *check, t_map *map)
{
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		check->f++;
		if (check_doubles(*check) == FAILURE || check_nb(split, map) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "C", 2) == 0)
	{
		check->c++;
		if (check_doubles(*check) == FAILURE || check_nb(split, map) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_decor_lines(char **split, t_check *check, t_map *map)
{
	if (check_texture_lines(split, check, map) == FAILURE)
		return (FAILURE);
	if (check_color_lines(split, check, map) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	split_condition(char **split, t_check *check, t_map *map)
{
	if (!split[1] || split[2])
	{
		free_tab(split);
		free_map_struct(map);
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("wrong decor setting or it does not exist\n", 2);
		return (FAILURE);
	}
	if (split[1])
	{
		if (check_decor_lines(split, check, map) == FAILURE)
			return (FAILURE);
	}
	else
		free_tab(split);
	return (SUCCESS);
}	

int	decor_analysis(t_map *map, t_check *check)
{
	int		i;
	char	**split;
	char	*tmp;

	i = -1;
	split = NULL;
	while (map->decor[++i])
	{
		tmp = map->decor[i];
		map->decor[i] = ft_strtrim(map->decor[i], " \t\n\v\f\r");
		free(tmp);
		if (check_space(map->decor[i]) == SUCCESS)
		{	
			split = ft_split(map->decor[i], ' ');
			if (split_condition(split, check, map) == FAILURE)
				return (FAILURE);
		}
		else
		{
			ft_putstr_fd("Error\n", 2);
			ft_putstr_fd("lines contain more than spaces\n", 2);
			return (FAILURE);
		}
		free_tab(split);
	}
	if (check_exist(*check) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
