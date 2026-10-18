/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:42:29 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/17 17:22:25 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	len_cal(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	while (s1[start] != '\0' && is_set_in(s1[start], set))
		start++;
	end = start;
	while (s1[end] != '\0')
		end++;
	while (end > start && is_set_in(s1[end - 1], set))
		end--;
	return (end - start);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	int		len;
	int		i;
	int		j;

	len = len_cal(s1, set);
	s2 = malloc(len + 1);
	if (s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0' && is_set_in(s1[i], set))
		i++;
	while (j < len)
	{
		s2[j] = s1[i];
		i++;
		j++;
	}
	s2[j] = '\0';
	return (s2);
}
