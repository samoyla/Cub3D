/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:07:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:57:54 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void tab_map(t_data *data, char *pathname)
{
	int	i;
	int	j;
	int	size;
	int	size_max;

	i = 0;
	j = data->map.count + 6;
	size = data->map.size - data->map.count + 6;
	if (size == 0)
		exit_free_destroy(data, "Map doesn't exist\n", FAILURE);
	size_max = max_width(&data->map.whole[j]);
	data->map.map = ft_calloc(size + 1, sizeof(char *));
	if (data->map.map == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	while (data->map.whole[j] != NULL)
	{
		if (ft_strchr(data->map.whole[j], '1') || ft_strchr(data->map.whole[j], '0')
			|| ft_strchr(data->map.whole[j], 'N') || ft_strchr(data->map.whole[j], 'S')
			|| ft_strchr(data->map.whole[j], 'W') || ft_strchr(data->map.whole[j], 'E'))
		{
			data->map.map[i++] = ft_strdup_space(data->map.whole[j], size_max);
			if (data->map.map[i - 1] == NULL)
				exit_free_destroy(data, "Problem in malloc\n", FAILURE);
		}
		j++;
	}
	data->map.map[i] = 0;
}
