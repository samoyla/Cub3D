/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decor_analysis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:12:05 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 10:59:25 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	split_and_check(t_data *data, char **str, t_check *check)
{
	char	**split;

	split = ft_split(*str, ' ');
	free(*str);
	if (split == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	if (split_condition(data, split, check) == FAILURE)
	{
		free_double_ptr_char(split);
		exit_free_destroy(data, "Wrong decor setting\n", FAILURE);
	}
	free_double_ptr_char(split);
}

void	decor_analysis(t_data *data, t_check *check)
{
	int		i;
	char	*str;

	i = -1;
	while (data->map.decor[++i])
	{
		str = ft_strtrim(data->map.decor[i], " \t\n\v\f\r");
		if (!str)
			exit_free_destroy(data, "Problem in malloc\n", FAILURE);
		if (check_space(str) == SUCCESS)
			split_and_check(data, &str, check);
		else
		{
			free(str);
			exit_free_destroy(data, "Lines contain more than spaces\n", FAILURE);
		}
	}
	if (check_exist(*check) == FAILURE)
		exit_free_destroy(data, "Wrong characters\n", FAILURE);
}
