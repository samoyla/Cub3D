/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 12:02:20 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/05 18:43:22 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	if_file_exists(char *pathname)
{
	int	fd;
	
	fd = open(pathname,O_RDONLY, F_OK);
	if (fd < 0)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS); 
}

int	if_dir(char *pathname)
{
	int	fd;

	fd = open(pathname, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (FAILURE);
	}
	close(fd);
	return (SUCCESS);
}

int	check_ext(char *name)
{
	int	i;

	i = strlen(name);
	while (name[i] != '.')
		i--;
	if (strcmp(&name[i + 1], "cub") != 0)
		return (FAILURE);
	return (SUCCESS);
}
