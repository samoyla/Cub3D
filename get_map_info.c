/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:32:36 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 11:17:38 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_tab_elements(char *pathname, t_map *map)
{
	tab_whole_map(pathname, map);
	tab_texture(pathname, map);
	tab_map(pathname, map);
}
