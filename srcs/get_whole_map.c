/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_whole_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:42:40 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 10:33:25 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_whitespaces_no_n(char c)
{
	if (c == ' ' || c == '\r'
		|| c == '\t' || c == '\v' || c == '\f')
		return (SUCCESS);
	return (FAILURE);
}

static int	if_n_end(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\n' && ft_whitespaces_no_n(str[i]) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	in_check_input(char *str)
{
	while (*str)
	{
		if (*str == '\n' && *(str + 1) && *(str + 1) == '\n' && if_n_end(str))
		{
			ft_putstr_fd("Error\nempty horizontal lines in map\n", 2);
			return (FAILURE);
		}
		else
			str++;
	}
	return (SUCCESS);
}

static int	check_input(char *str, int *flag_start)
{
	while (*str)
	{
		while (*str && *str != '\n')
		{
			while (*str && !ft_whitespaces_no_n(*str))
				str++;
			if (*str == '1')
			{
				*flag_start = 1;
				break ;
			}
			else
				break ;
		}
		if (*flag_start)
			break ;
		while (*str && *str != '\n')
			str++;
		if (*str != '\0')
			str++;
	}
	if (in_check_input(str) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	get_whole_map(t_data *data, char **av)
{
	int		i;
	int		flag_start;

	i = 0;
	flag_start = 0;
	read_input(data, av);
	if (check_input(data->map.input, &flag_start) == FAILURE)
	{
		free(data->map.input);
		exit (FAILURE);
	}
	data->map.whole = ft_split(data->map.input, '\n');
	if (data->map.whole == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	while (data->map.whole[i])
		i++;
	data->map.size = i;
	free(data->map.input);
	data->map.input = NULL;
}
