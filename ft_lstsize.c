/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 15:57:21 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/21 16:06:02 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_lstsize(t_list *lst)
{
	unsigned int	i;

	i = 0;
	if (lst == NULL)
		return (0);
	while (lst != NULL)
	{
		i++;
		lst = lst -> next;
	}
	return (i);
}
