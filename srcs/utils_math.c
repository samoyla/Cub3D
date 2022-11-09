/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 21:15:52 by iguscett          #+#    #+#             */
/*   Updated: 2022/11/06 17:15:32 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	norm_vector(t_vect v)
{
	return (sqrt((v.vx * v.vx) + (v.vy * v.vy)));
}

double	norm_two_points(t_posi p1, t_posi p2)
{
	return (sqrt((p1.x - p2.x) * (p1.x - p2.x)
			+ (p1.y - p2.y) * (p1.y - p2.y)));
}

double	absd(double a)
{
	if (a >= 0)
		return (a);
	return (-a);
}

void	z_rotation(t_data *data, t_posi *p, double angle)
{
	double	x;
	double	y;

	x = p->x - data->player.pos.x;
	y = p->y - data->player.pos.y;
	p->y = data->player.pos.y + y * cos(angle) - x * sin(angle);
	p->x = data->player.pos.x + y * sin(angle) + x * cos(angle);
}
