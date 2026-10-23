/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:02:57 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/23 12:40:23 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	processlist(void *content, t_list **lst1,
		t_list **tmp, void (*del)(void *))
{
	t_list	*new_node;

	new_node = ft_lstnew(content);
	if (!new_node)
	{
		del(content);
		return (0);
	}
	if (!*lst1)
		*lst1 = new_node;
	else
		(*tmp)->next = new_node;
	*tmp = new_node;
	return (1);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst1;
	t_list	*tmp;
	void	*content;

	if (!f || !del)
		return (NULL);
	lst1 = NULL;
	tmp = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!processlist(content, &lst1, &tmp, del))
		{
			ft_lstclear(&lst1, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (lst1);
}
