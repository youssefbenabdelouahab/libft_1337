/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:41:40 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/25 11:36:26 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_backward(unsigned char *dst,
		const unsigned char *src, size_t len)
{
	while (len > 0)
	{
		len--;
		dst[len] = src[len];
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*s1;
	const unsigned char	*s2;

	if (dst == src)
		return (dst);
	s1 = (unsigned char *)dst;
	s2 = (const unsigned char *)src;
	if (s1 < s2)
	{
		i = 0;
		while (i < len)
		{
			s1[i] = s2[i];
			i++;
		}
	}
	else
	{
		copy_backward(s1, s2, len);
	}
	return (dst);
}
