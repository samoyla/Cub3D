/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_analyze_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:32:36 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 16:19:00 by iguscett         ###   ########.fr       */
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

void	get_map_tex_and_colors(t_data *data, char *pathname)
{
	int	i;
	int	j;
	int	end_of_whole;

	i = -1;
	j = 0;
	data->map.decor = ft_calloc(6 + 1, sizeof(char *));
	data->map.decor[6] == NULL;
	if (data->map.decor == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	while (data->map.whole[++i])
	{
		if (check_line_space(data->map.whole[i]) == SUCCESS)
		{
			if (j <= 5)
			{
				data->map.decor[j] = data->map.whole[i];
				j++;
			}
			else
			{
				data->map.index = i;
				break ;
			}
		}
	}
	end_of_whole = data->map.size;
	while (data->map.whole[data->map.index])
	{
		while (check_line_space(data->map.whole[data->map.index]) == FAILURE)
			data->map.index++;
		break ;
		data->map.index++;
	}
	data->map.count = end_of_whole - data->map.index;
}

void	get_and_analyze_map(t_data *data,
	t_check *check, char *pathname, char **av)
{
	get_whole_map(data, av);
	get_map_tex_and_colors(data, pathname);
	decor_analysis(data, check);
	tab_map(data, pathname);
	map_analysis(data);
}
