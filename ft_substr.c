/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:48:08 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/18 14:01:18 by yben-abd         ###   ########.fr       */
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
	s1 = malloc(len + 1);
	if (s1 == NULL)
		return (NULL);
	i = 0;
	while (start < len_total && s[start] != '\0' && i < len)
	{
		s1[i] = s[start];
		i++;
		start++;
	}
	s1[i] = '\0';
	return (s1);
}
