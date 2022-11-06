/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:10:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/30 20:52:03 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void free_double_ptr_char(char **str)
{
	int i;

	i = -1;
	if (str != NULL)
	{
		while (str[++i])
			free(str[i]);
		free(str);
	}
}

void	check_fd(int fd)
{
	if (fd < 0)
	{
		perror("fd:");
		exit(FAILURE);
	}
}

int	if_str_digit(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (ft_isdigit(s[i]) == 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	digit_size(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_atoi(&s[i]) > 255 || ft_atoi(&s[i]) < 0)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}
