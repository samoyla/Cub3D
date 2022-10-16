/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:47:52 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/16 12:34:09 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_doubles(t_check *check)
{
	if (check->no > 1 || check->so > 1 || check->we > 1 || check->ea > 1 
		|| check->f > 1 || check->c > 1)
	{
		printf("Error\n");
		printf("duplication is found\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
