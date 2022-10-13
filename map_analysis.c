/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_analysis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:12:05 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 17:24:47 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	texture_analysis(char **split, t_check *check)
{
	if (strncmp(split[0], "NO", 3) == 0)
	{
		if (check_north(check, split) == FAILURE)
			return (FAILURE);
	}
	if (strncmp(split[0], "SO", 3) == 0)
	{
		if (check_south(check, split) == FAILURE)
			return (FAILURE);
	}
	if (strncmp(split[0], "WE", 3) == 0)
	{
		if (check_west(check, split) == FAILURE)
			return (FAILURE);
	}
	if (strncmp(split[0], "EA", 3) == 0)
	{
		if (check_east(check, split) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	color_analysis(char **split, t_check *check)
{
	if (strncmp(split[0], "F", 2) == 0)
	{
		check->f++;
		if (check_doubles(check) == FAILURE)
			return (FAILURE);
	}
	if (strncmp(split[0], "S", 2) == 0)
	{
		check->c++;
		if (check_doubles(check) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	check_decor_lines(char **split, t_check *check)
{
	if (texture_analysis(split, check) == FAILURE)
		return (FAILURE);
	if (color_analysis(split, check) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	split_condition(char **split,t_check *check)
{
	if (!split[1])
	{
		printf("Error\n");
		printf("wrong decor setting");
		return (FAILURE);
	}
	if (split[1])
	{
		if (check_decor_lines(split, check) == FAILURE)
			return (FAILURE);
	}
	if (split[2])
	{
		printf("Error\n");
		printf("too much elements in decor");
		return (FAILURE);
	}
	else
		free_tab(split);
	return (SUCCESS);
}	

static int	split_decor(char **decor, t_check *check)
{
	int	i;

	char	**split;
	i = 0;
	split = NULL;
	while (decor[i])
	{
		if (if_not_spaces(decor[i]) == SUCCESS)
		{	
			split = ft_split(decor[i], ' ');
			if (split_condition(split, check) == FAILURE)
				return (FAILURE);
				
		}
		else
		{
			printf("Error\n");
			printf("lines contain more than spaces\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	decor_analysis(t_map *map, t_check *check)
{
	int		i;

	i = 0;
	if (split_decor(map->decor, check) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
