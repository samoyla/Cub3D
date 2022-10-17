/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:43:41 by marvin            #+#    #+#             */
/*   Updated: 2021/12/02 09:16:56 by masamoil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*suivant;

	if (!lst || !del)
		return ;
	tmp = *lst;
	while (tmp)
	{
		suivant = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = suivant;
	}
	(*lst) = NULL;
}
