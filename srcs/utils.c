/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:10:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/28 17:31:57 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_fd(int fd)
{
	if (fd < 0)
	{
		perror("fd:");
		exit(FAILURE);
	}
}

void	print_tab(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("tab %s\n", tab[i]);
		i++;
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
