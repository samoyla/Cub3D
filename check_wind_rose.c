/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wind_rose.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:57:32 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 13:57:22 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_north(t_check *check, char **split)
{
	int	fd;

	fd = open(split[1], O_RDONLY);
	check->no++;
	if (check_doubles(check) == FAILURE)
		return (FAILURE);
	if (fd < 0)
	{
		printf("Error\n");
		printf("no texture path is not valid\n");
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);

}

int	check_south(t_check *check, char **split)
{
	int	fd;

	fd = open(split[1], O_RDONLY);
	check->so++;
	if (check_doubles(check) == FAILURE)
		return (FAILURE);
	if (fd < 0)
	{
		printf("Error\n");
		printf("so texture path is not valid\n");
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);

}

int	check_west(t_check *check, char **split)
{
	int	fd;

	fd = open(split[1], O_RDONLY);
	check->we++;
	if (check_doubles(check) == FAILURE)
		return (FAILURE);
	if (fd < 0)
	{
		printf("Error\n");
		printf("we texture path is not valid\n");
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	check_east(t_check *check, char **split)
{
	int	fd;

	fd = open(split[1], O_RDONLY);
	check->ea++;
	if (check_doubles(check) == FAILURE)
		return (FAILURE);
	if (fd < 0)
	{
		printf("Error\n");
		printf("ea texture path is not valid\n");
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}
