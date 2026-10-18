/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:48:08 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/18 16:18:42 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,	size_t len)
{
	char	*s1;
	size_t	i;
	size_t	len_total;

	if (s == NULL)
		return (NULL);
	len_total = ft_strlen(s);
	if (start >= len_total)
		len = 0;
	else if (len > len_total - start)
		len = len_total - start;
	s1 = malloc(len + 1);
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		s1[i] = s[start + i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
