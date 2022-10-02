/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 13:26:26 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/02 15:14:40 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CUB3D_H_
#define _CUB3D_H_

# include "mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include <stdint.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>

#define WIDTH 1200
#define	HEIGHT 800
#define MLX_ERROR 1

typedef struct s_pos
{
	float	x;
	float	y;
}	t_pos;

typedef struct	s_data 
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

//init.c
t_data	*init_data(t_data *data, char *name);
//utils.c
void	ft_error(void);

#endif
