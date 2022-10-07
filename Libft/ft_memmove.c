/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 15:49:38 by marvin            #+#    #+#             */
/*   Updated: 2021/12/01 14:17:56 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	char		tmp;

	d = dest;
	s = src;
	if (!dest && !src)
		return (NULL);
	if (d > s)
	{
		while (n > 0)
		{
			tmp = s[n - 1];
			d[n - 1] = tmp;
			n--;
		}
	}
	else
		ft_memcpy(d, s, n);
	return (dest);
}
