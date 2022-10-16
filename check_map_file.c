/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:32:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/14 15:52:21 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("euh, wrong number of arguments\n", 2);
		return (FAILURE);
	}	
	return (SUCCESS);
}

static int	if_file_exists(char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY, F_OK);
	if (fd < 0)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

static int	if_dir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	check_ext(char *name)
{
	int	i;

	i = ft_strlen(name);
	while (name[i] != '.')
		i--;
	if (ft_strcmp(&name[i + 1], "cub") != 0)
		return (FAILURE);
	return (SUCCESS);
}


int	check_file(char *s)
{
	if (if_dir(s) == FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("It's a dirtectory\n", 2);
		return (FAILURE);
	}
	if (s[0] == '.')
	{
		ft_putstr_fd("Error\nWrong format\n", 2);
		return (FAILURE);
	}
	if (if_file_exists(s) == FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("File does not exist\n", 2);
		return (FAILURE);
	}
	if (check_ext(s) == FAILURE)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("Wrong file extension\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
