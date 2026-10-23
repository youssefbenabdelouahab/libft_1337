/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:22:11 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/23 12:24:01 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp1;

	if (lst && del)
	{
		tmp = *lst;
		while (tmp != NULL)
		{
			tmp1 = tmp->next;
			ft_lstdelone(tmp, del);
			tmp = tmp1;
		}
		*lst = NULL;
	}
}
