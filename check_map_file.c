/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:32:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/12 17:45:42 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_args(int ac)
{
	if (ac != 2)
	{
		printf("euh, wrong number of arguments\n");
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

	i = strlen(name);
	while (name[i] != '.')
		i--;
	if (strcmp(&name[i + 1], "cub") != 0)
		return (FAILURE);
	return (SUCCESS);
}


int	check_file(char *s)
{
	if (if_dir(s) == FAILURE)
	{
		printf("It's a dirtectory");
		return (FAILURE);
	}
	if (if_file_exists(s) == FAILURE)
	{
		printf("File does not exist\n");
		return (FAILURE);
	}
	if (check_ext(s) == FAILURE)
	{
		printf("wrong file extension\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
