/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 11:15:24 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tab_map(t_data *data)
{
	int	i;
	int	j;
	int	size_max;

	i = 0;
	j = data->map.index;
	if (j == 0)
		exit_free_destroy(data, "Map does not exist\n", FAILURE);
	size_max = max_width(&data->map.whole[j], data);
	data->map.map = ft_calloc(data->map.count + 1, sizeof(char *));
	if (data->map.map == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	while (data->map.whole[j] != NULL)
	{
		data->map.map[i++] = ft_strdup_space(data->map.whole[j], size_max);
		if (data->map.map[i - 1] == NULL)
			exit_free_destroy(data, "Problem in malloc\n", FAILURE);
		j++;
	}
	data->map.map[i] = 0;
	return (SUCCESS);
}
