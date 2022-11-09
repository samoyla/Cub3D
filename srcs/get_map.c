/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:27:24 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/06 16:21:38 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_texture(t_data *data)
{
	int		i;
	char	*str;
	char	**wind_rose;

	i = -1;
	while (data->map.decor[++i] && i < 6)
	{
		str = ft_strtrim(data->map.decor[i], " \t\n\v\f\r");
		wind_rose = ft_split(str, ' ');
		if (wind_rose == NULL)
			exit_free_destroy(data, "Problem in malloc\n", FAILURE);
		if (ft_strncmp(wind_rose[0], "NO", 2) == 0)
			data->map.no = ft_strdup(wind_rose[1]);
		else if (ft_strncmp(wind_rose[0], "SO", 2) == 0)
			data->map.so = ft_strdup(wind_rose[1]);
		else if (ft_strncmp(wind_rose[0], "WE", 2) == 0)
			data->map.we = ft_strdup(wind_rose[1]);
		else if (ft_strncmp(wind_rose[0], "EA", 2) == 0)
			data->map.ea = ft_strdup(wind_rose[1]);
		free_double_ptr_char(wind_rose);
		free(str);
	}
	if (data->map.no == NULL || data->map.so == NULL
		|| data->map.ea == NULL || data->map.we == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
}

static void	get_color_values(t_data *data, char *str, char c)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (rgb == NULL)
		exit_free_destroy(data, "Problem in malloc\n", FAILURE);
	if (c == 'F')
	{
		data->map.f_red = ft_atoi(rgb[0]);
		data->map.f_green = ft_atoi(rgb[1]);
		data->map.f_blue = ft_atoi(rgb[2]);
	}
	else if (c == 'C')
	{
		data->map.c_red = ft_atoi(rgb[0]);
		data->map.c_green = ft_atoi(rgb[1]);
		data->map.c_blue = ft_atoi(rgb[2]);
	}
	free_double_ptr_char(rgb);
}

static void	get_color(t_data *data)
{
	int		i;
	char	**color_line;

	i = -1;
	while (data->map.decor[++i] && i < 6)
	{
		color_line = ft_split(data->map.decor[i], ' ');
		if (color_line == NULL)
			exit_free_destroy(data, "Problem in malloc\n", FAILURE);
		if (ft_strncmp(color_line[0], "F", 2) == 0)
			get_color_values(data, color_line[1], 'F');
		if (ft_strncmp(color_line[0], "C", 2) == 0)
			get_color_values(data, color_line[1], 'C');
		free_double_ptr_char(color_line);
	}
	data->map.floor = encode_rgb(data->map.f_red,
			data->map.f_green, data->map.f_blue);
	data->map.ceilling = encode_rgb(data->map.c_red,
			data->map.c_green, data->map.c_blue);
}

static void	get_map_size(t_data *data)
{
	long	y;
	long	x;

	y = 0;
	if (data->map.map[0])
		x = ft_strlen(data->map.map[0]);
	while (data->map.map[(int)y])
	{
		if (ft_strlen(data->map.map[(int)y]) > x)
			x = ft_strlen(data->map.map[y]);
		y++;
		if (y > INT_MAX)
			exit_free_destroy(data, "Map too big\n", FAILURE);
	}
	if (x > INT_MAX)
		exit_free_destroy(data, "Map too big\n", FAILURE);
	data->map.xsize = x;
	data->map.ysize = y;
}

void	get_map(t_data *data)
{
	get_texture(data);
	get_color(data);
	get_map_size(data);
}
