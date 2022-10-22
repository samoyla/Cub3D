/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_screen_points.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 18:11:32 by iguscett          #+#    #+#             */
/*   Updated: 2022/10/21 18:40:07 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void set_screen_points(t_data *data)
{
	data->player.screen.pleft.x = data->player.pos.x + HALF;
	data->player.screen.pleft.y = data->player.pos.y + DIST;
	data->player.screen.pright.x = data->player.pos.x - HALF;
	data->player.screen.pright.y = data->player.pos.y + DIST;
	z_rotation(data, &data->player.screen.pleft, data->player.angle);
	z_rotation(data, &data->player.screen.pright, data->player.angle);
	data->player.screen.incr = (HALF * 2) / data->width;
	printf("2HALF:%f and incr:%f, width:%d\n", 2 * HALF, data->player.screen.incr, data->width);
	printf("Width*incr:%f\n", data->width * data->player.screen.incr);
	data->player.screen.pleft.z = 0.5;

}
