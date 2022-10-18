/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iguscett <iguscett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:10:11 by masamoil          #+#    #+#             */
/*   Updated: 2022/10/18 16:41:22 by iguscett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_fd(int fd)
{
	if (fd < 0)
		ft_putstr_fd("Erro\nFile doesn't exist\n", 2);

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

int	if_str_digit(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_isdigit(s[i]) == 0)
			return (FAILURE);
	return (SUCCESS);
}

int	digit_size(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (ft_atoi(&s[i]) > 255 || ft_atoi(&s[i]) < 0)
			return (FAILURE);
	return (SUCCESS);
}
