/* ************************************************************************ */
/*                                                                          */
/*                                                       :::      ::::::::  */
/*  read_input.c                                       :+:      :+:    :+:  */
/*                                                   +:+ +:+         +:+    */
/*  By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+       */
/*                                               +#+#+#+#+#+   +#+          */
/*  Created: 2022/10/09 18:18:24 by iguscett          #+#    #+#            */
/*  Updated: 2022/10/21 16:07:17 by masamoil         ###   ########.fr      */
/*                                                                          */
/* ************************************************************************ */

#include "cub3d.h"

static char    ft_strjoin_free(chars1, char const *s2)
{
    char    temp;
    size_t    it;
    size_t    it2;

    it = 0;
    while (s1 && s1[it])
        it++;
    temp = malloc(sizeof(char) (it + ft_strlen(s2) + 1));
    if (!temp)
        return (NULL);
    it = 0;
    while (s1 && s1[it])
    {
        temp[it] = s1[it];
        it++;
    }
    it2 = -1;
    while (s2[++it2])
    {
        temp[it] = s2[it2];
        it++;
    }
    temp[it] = '\0';
    if (s1)
        free(s1);
    return (temp);
}

static void    ft_init_data_read(t_readdata_read)
{
    data_read->eof = 0;
    data_read->b_read = 0;
    data_read->temp = NULL;
}

static void close_and_exit(t_read data_read)
{
    close(data_read->fd);
    ft_error("Problem in malloc\n");
}

void read_input(t_map *map, char **argv)
{
    t_read        data_read;
    static char    buff[1024];

    ft_init_data_read(&data_read);
    data_read.fd = open(argv[1], O_RDONLY);
    if (data_read.fd < 0)
    {
        ft_putstr_fd("Problem encountered while reading the file\n", 2);
	exit (FAILURE);
    }
    while (!data_read.eof)
    {
        data_read.b_read = read(data_read.fd, buff, 1024);
        data_read.temp = ft_strjoin_free(data_read.temp, buff);
        if (data_read.temp == NULL)
            close_and_exit(&data_read);
        ft_bzero(buff, 1024);
        if (data_read.b_read < 1024)
            data_read.eof = 1;
    }
    close(data_read.fd);
    map->whole = data_read.temp;
}
