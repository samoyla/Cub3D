/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wind_rose_n_colors.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:08:51 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/19 16:24:35 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_doubles(t_check check)
{
	if (check.no > 1 || check.so > 1 || check.we > 1 || check.ea > 1 
		|| check.f > 1 || check.c > 1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("duplication is found\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_exist(t_check check)
{
	if (check.no != 1 || check.so != 1 || check.we != 1 || check.ea != 1 
		|| check.f != 1 || check.c != 1)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("wrong characters\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	path_ext(char *name)
{
	int	i;

	i = ft_strlen(name);
	while (name[i] != '.')
		i--;
	if (ft_strcmp(&name[i + 1], "xpm") != 0)
		return (FAILURE);
	return (SUCCESS);
}

int	check_windrose(t_check *check, char **split)
{
	int	fd;

	fd = open(split[1], O_RDONLY);
	if (check_doubles(*check) == FAILURE)
		return (FAILURE);
	if (fd < 0)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("path of texture is not valid\n", 2);
		free_tab(split);
		return (FAILURE);
	}
	ft_strtrim(split[1], " \t\n\v\f\r");
	if (path_ext(split[1]) == FAILURE)
	{
		ft_putstr_fd("Error\nwrong texture extention\n", 2);
		free_tab(split);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	check_nb(char *str)
{
	char	**split_nb;
	int		i;


	split_nb = ft_split(str, ',');
	if (split_nb == NULL)
		return (FAILURE);
	print_tab(split_nb);
	i = -1;
	while (split_nb[++i])
	{
		if (if_str_digit(split_nb[i]) == FAILURE
			|| digit_size(split_nb[i]) == FAILURE)
		{
			ft_putstr_fd("rgb problem\n", 2);
			return (FAILURE);
		}
	}
	if (i != 3)
	{
		ft_putstr_fd("format of rgb is incorrect\n", 2);
		free_tab(split_nb);
		return (FAILURE);
	}
	return (SUCCESS);
}
