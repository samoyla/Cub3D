/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:09 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/18 12:33:28 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max_width(char **mapi, t_map *map)
{
	int	i;
	int	size;

	i = 0;
	if (!mapi[i])
	{
		ft_putstr_fd("map does not exist\n", 2);
		free_map_struct(map);
		exit (FAILURE);
	}
	size = ft_strlen(mapi[i]);
	while (mapi[i])
	{
		if (size < ft_strlen(mapi[i]))
			size = ft_strlen(mapi[i]);
		i++;
	}
	return (size);	
}

char	*ft_strdup_space(char *s, int size)
{
	char	*dest;
	int	i;

	i = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
		
	}
	while (i < size)
	{
		dest[i] = ' ';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
