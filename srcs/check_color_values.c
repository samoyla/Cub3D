/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 10:37:14 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/03 10:37:31 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_split_nb(int i, char **split_nb, char **str)
{
	if (i != 3)
	{
		ft_putstr_fd("format of rgb is incorrect\n", 2);
		free_tab(split_nb);
		free_tab(str);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_nb(char **str, t_map *map)
{
	char	**split_nb;
	int		i;

	split_nb = ft_split(str[1], ',');
	if (split_nb == NULL)
		return (FAILURE);
	i = -1;
	while (split_nb[++i])
	{
		if (if_str_digit(split_nb[i]) == FAILURE
			|| digit_size(split_nb[i]) == FAILURE)
		{
			free_tab(split_nb);
			free_tab(str);
			ft_putstr_fd("rgb problem\n", 2);
			return (FAILURE);
		}
	}
	if (check_split_nb(i, split_nb, str) == FAILURE)
		return (FAILURE);
	free_tab(split_nb);
	return (SUCCESS);
}
