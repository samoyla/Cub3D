/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:47:52 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 15:40:44 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_doubles(t_check *check)
{
	if (check->f > 1 || check->c > 1)
	{
		printf("Error\n");
		printf("double color character\n");
		return (FAILURE);
	}
	if (check->no > 1 || check->so > 1 || check->we > 1 || check->ea > 1)
	{
		printf("Error\n");
		printf("doubles texture character\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_doubles_troubles(t_check *check)
{
	if (check->f != 1 || check->c != 1)
	{
		printf("Error\n");
		printf("double color character\n");
		return (FAILURE);
	}
	if (check->no != 1 || check->so != 1 || check->we != 1 || check->ea != 1)
	{
		printf("Error\n");
		printf("doubles texture character\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
