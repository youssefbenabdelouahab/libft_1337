/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:32:22 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/23 22:02:53 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = malloc(len_s1 + len_s2 + 1);
	if (s3 == NULL)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (j < len_s2)
	{
		s3[i++] = s2[j++];
	}
	s3[i] = '\0';
	return (s3);
}
