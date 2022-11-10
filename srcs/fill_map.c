/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:45:09 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 11:17:56 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max_width(char **mapi, t_data *data)
{
	int	i;
	int	size;

	i = 0;
	if (!mapi[i])
		exit_free_destroy(data, "Map does not exist\n", FAILURE);
	size = ft_strlen(mapi[i]);
	while (mapi[i])
	{
		if (size < (int)ft_strlen(mapi[i]))
			size = (int)ft_strlen(mapi[i]);
		i++;
	}
	return (size);
}

char	*ft_strdup_space(char *s, int size)
{
	char	*dest;
	int		i;

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
