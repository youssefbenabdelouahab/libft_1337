/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 18:14:11 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/17 21:36:35 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*copy;
	size_t		i;
	size_t		strlen;

	strlen = ft_strlen(s1);
	copy = malloc(strlen + 1);
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < strlen)
	{
		copy[i] = (char) s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
