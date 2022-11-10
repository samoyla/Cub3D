/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 17:13:30 by masamoil          #+#    #+#             */
/*   Updated: 2022/11/10 11:17:33 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

double	sign(t_posi p, t_hpt pa, t_hpt pb)
{
	double	a;
	double	b;

	a = (p.x - pb.x_hud) * (pa.y_hud - pb.y_hud);
	b = (pa.x_hud - pb.x_hud) * (p.y - pb.y_hud);
	return (a - b);
}

int	is_in_triangle(t_data *data, t_posi p)
{
	double	a;
	double	b;
	double	c;
	int		has_neg;
	int		has_pos;

	a = sign(p, data->hud.tri.p1, data->hud.tri.p2);
	b = sign(p, data->hud.tri.p2, data->hud.tri.p3);
	c = sign(p, data->hud.tri.p3, data->hud.tri.p1);
	has_neg = 0;
	if ((a < 0) || (b < 0) || (c < 0))
		has_neg = 1;
	has_pos = 0;
	if ((a > 0) || (b > 0) || (c > 0))
		has_pos = 1;
	if (has_neg && has_pos)
		return (0);
	return (1);
}

void	render_player(t_data *data, int color)
{
	t_posi	p;

	p.x = data->player.pos.x * data->hud.xt - 0.25 * data->hud.xt -1;
	p.y = data->player.pos.y * data->hud.yt - 0.25 * data->hud.yt -1;
	while (p.x <= data->player.pos.x * data->hud.xt + 0.25 * data->hud.xt)
	{
		p.y = data->player.pos.y * data->hud.yt - 0.25 * data->hud.yt -1;
		while (p.y <= data->player.pos.y
			* data->hud.yt + 0.25 * data->hud.yt)
		{
			if (is_in_triangle(data, p))
				img_pix_put(&data->img, p.x, p.y, color);
			p.y++;
		}
		p.x++;
	}
}

int	render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (1);
	ray_tracing(data);
	render_hud(data, STRONG_BLUE);
	render_player(data, YELLOW);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}
