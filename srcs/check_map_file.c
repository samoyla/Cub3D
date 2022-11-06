/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:32:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 15:58:27 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_if_is_dir(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_DIRECTORY);
	if (fd != -1)
	{
		if (fd >= 0)
			close(fd);
		exit_free_destroy(data, "Input is a directory\n", FAILURE);
	}
	if (fd >= 0)
		close(fd);
}

static void check_if_file_exists(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY, F_OK);
	if (fd < 0)
	{
		if (fd >= 0)
			close(fd);
		exit_free_destroy(data, "File does not exist or is protected\n", FAILURE);
	}
	if (fd >= 0)
		close(fd);
}

static void check_extension(t_data *data, char *name) // redo cause wrong
{
	int len;

	if (ft_strcmp(name, ".cub") == 0)
		exit_free_destroy(data, "Wrong file\n", FAILURE);
	len = ft_strlen(name);
	while (len >= 0 && name[len] != '.')
		len--;
	if (len == -1)
		exit_free_destroy(data, "Wrong file extension\n", FAILURE);
	if (ft_strcmp(&name[len], ".cub") != 0)
		exit_free_destroy(data, "Wrong file extension\n", FAILURE);
}

void check_nb_args_and_file(t_data *data, int argc, char **argv)
{
	if (argc != 2)
		exit_free_destroy(data, "Wrong number of arguments\n", FAILURE);
	check_if_is_dir(data, argv[1]);
	check_if_file_exists(data, argv[1]);
	check_extension(data, argv[1]);
}
