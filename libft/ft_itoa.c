/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:30:45 by marvin            #+#    #+#             */
/*   Updated: 2021/11/29 12:54:12 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long nb)
{
	int	len;

	if (nb <= 0)
		len = 1;
	else
		len = 0;
	while (nb != 0)
	{
		nb = nb / 10;
		len ++;
	}
	return (len);
}

static void	ft_conditions(long nb, char *str, long len)
{
	if (nb == 0)
	{
		str[0] = '0';
	}
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb > 0)
	{
		str[len--] = nb % 10 + '0';
		nb = nb / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*dest;
	long	len;
	long	nb;

	nb = n;
	len = ft_len(nb);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	len--;
	ft_conditions(nb, dest, len);
	return (dest);
}
