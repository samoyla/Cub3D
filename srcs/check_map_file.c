/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:32:42 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/30 18:02:59 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void check_if_is_dir(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		err_free_ptrs(data, "Input is a directory\n");
	}
	close(fd);
}

static void check_if_file_exists(t_data *data, char *pathname)
{
	int	fd;

	fd = open(pathname, O_RDONLY, F_OK);
	if (fd < 0)
	{
		close(fd);
		err_free_ptrs(data, "File does not exist or is protected\n");
	}
	close(fd);
}

static void check_extension(t_data *data, char *name) // redo cause wrong
{
	int len;

	if (ft_strcmp(name, ".cub") == 0)
		err_free_ptrs(data, "Wrong file\n");
	len = ft_strlen(name);
	while (len >= 0 && name[len] != '.')
		len--;
	if (len == -1)
		err_free_ptrs(data, "Wrong file extension\n");
	if (ft_strcmp(&name[len], ".cub") != 0)
		err_free_ptrs(data, "Wrong file extension\n");
}

void check_nb_args_and_file(t_data *data, int argc, char **argv)
{
	if (argc != 2)
		err_free_ptrs(data, "Wrong number of arguments\n");
	check_if_is_dir(data, argv[1]);
	check_if_file_exists(data, argv[1]);
	check_extension(data, argv[1]);
}
