/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 12:35:55 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/17 12:50:00 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	j = dst_len;
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	while (src[i] != '\0' && i < dstsize - dst_len - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	return (src_len + dst_len);
}
