/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masamoil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:10:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/13 15:23:30 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(void)
{
	perror("Error:");
}

void	print_tab(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		printf("tab[%d]%s\n", i, tab[i]);
		i++;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

int	if_digit(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	digit_size(int nb)
{
	if (nb > 255 || nb < 0)
		return (FAILURE);
	return (SUCCESS);
}
