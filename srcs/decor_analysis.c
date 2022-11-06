/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decor_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:12:05 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:58:20 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_lines(char **split, t_check *check)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		check->no++;
		if (check_windrose(check, split) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		check->so++;
		if (check_windrose(check, split) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		check->we++;
		if (check_windrose(check, split) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		check->ea++;
		if (check_windrose(check, split) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_color_lines(char **split, t_check *check)
{
	if (ft_strncmp(split[0], "F", 2) == 0)
	{
		check->f++;
		if (check_doubles(*check) == FAILURE || check_nb(split[1]) == FAILURE)
			return (FAILURE);
	}
	if (ft_strncmp(split[0], "C", 2) == 0)
	{
		check->c++;
		if (check_doubles(*check) == FAILURE || check_nb(split[1]) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_decor_lines(char **split, t_check *check)
{
	if (check_texture_lines(split, check) == FAILURE)
		return (FAILURE);
	if (check_color_lines(split, check) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	split_condition(char **split, t_check *check)
{
	if (!split[1] || split[2])
		return (FAILURE);
	if (check_decor_lines(split, check) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < 32)
			return (FAILURE);
	}
	return (SUCCESS);
}

void decor_analysis(t_data *data, t_check *check)
{
	int		i;
	char	**split;
	char	*str;

	i = -1;
	while (data->map.decor[++i])
	{
		str = ft_strtrim(data->map.decor[i], " \t\n\v\f\r");
		if (check_space(str) == SUCCESS)
		{
			split = ft_split(str, ' ');
			free(str);
			if (split == NULL)
				exit_free_destroy(data, "Problem in malloc\n", FAILURE);
			if (split_condition(split, check) == FAILURE)
			{
				free_double_ptr_char(split);
				exit_free_destroy(data, "Wrong decor setting\n", FAILURE);
			}
			free_double_ptr_char(split);
		}
		else
		{
			free(str);
			exit_free_destroy(data, "Lines contain more than spaces\n", FAILURE);
		}
	}
	if (check_exist(*check) == FAILURE)
		exit_free_destroy(data, "Wrong charcters\n", FAILURE);
}
