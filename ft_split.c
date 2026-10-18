/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 13:59:25 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/18 19:19:11 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	in_word;
	int	cnt;

	i = 0;
	in_word = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			in_word = 0;
		}
		else
		{
			if (s[i] != c && !in_word)
			{
				in_word = 1;
				cnt++;
			}
		}
		i++;
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		nbr_words;
	int		i;

	nbr_words = count_word(s);
	str = malloc((sizeof(char *) * nbr_words) + 1);
	i = 0;
	while (i < nbr_words)
	{
		
	}
}