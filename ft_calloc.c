/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:58:26 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/17 12:49:04 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	sizefinal;
	size_t	i;
	void	*ptr;

	sizefinal = count * size;
	ptr = malloc(sizefinal);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < sizefinal)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
