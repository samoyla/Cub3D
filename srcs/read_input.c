/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:50:26 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 16:50:29 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_init_data_read(t_read *data_read)
{
	data_read->eof = 0;
	data_read->b_read = 0;
	data_read->temp = NULL;
}

static char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*temp;
	size_t	it;

	it = 0;
	while (s1 && s1[it])
		it++;
	temp = malloc(sizeof(char) * (it + ft_strlen(s2) + 1));
	if (!temp)
		return (NULL);
	it = 0;
	while (s1 && s1[it])
	{
		temp[it] = s1[it];
		it++;
	}
	while (*s2)
	{
		temp[it] = *s2++;
		it++;
	}
	temp[it] = '\0';
	if (s1)
		free(s1);
	return (temp);
}

static void	close_and_exit(t_data *data, t_read *data_read)
{
	if (data_read->fd >= 0)
		close(data_read->fd);
	exit_free_destroy(data, "Problem in malloc\n", FAILURE);
}

static void	empty_file(ssize_t	b_read)
{
	if (b_read == 0)
	{
		ft_putstr_fd("File is empty\n", 2);
		exit (FAILURE);
	}
}

void	read_input(t_data *data, char **argv)
{
	t_read		data_read;
	static char	buff[1024];

	ft_init_data_read(&data_read);
	data_read.fd = open(argv[1], O_RDONLY);
	if (data_read.fd < 0)
		exit_free_destroy(data,
			"Problem encountered while reading the file\n", FAILURE);
	while (!data_read.eof)
	{
		data_read.b_read = read(data_read.fd, buff, 1024);
		empty_file(data_read.b_read);
		data_read.temp = ft_strjoin_free(data_read.temp, buff);
		if (data_read.temp == NULL)
			close_and_exit(data, &data_read);
		ft_bzero(buff, 1024);
		if (data_read.b_read < 1024)
			data_read.eof = 1;
	}
	if (data_read.fd >= 0)
		close(data_read.fd);
	data->map.input = data_read.temp;
}
