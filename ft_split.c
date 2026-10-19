/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 13:59:25 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/19 13:40:06 by yben-abd         ###   ########.fr       */
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

static int	count_len(char const *s, char c, int start)
{
	int	i;

	i = 0;
	while (s[start] != '\0' && s[start] != c)
	{
		i++;
		start++;
	}
	return (i);
}

static void	ft_free(char **str, int x)
{
	int	i;

	i = 0;
	if (str[x] == NULL)
	{
		while (i < x)
		{
			free(str[i]);
			i++;
		}
		free(str);
		return ;
	}
}

static	void	ft_remplir(char **str, char const *s, int nbr_words, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = count_len(s, c, i);
			if (j < nbr_words)
			{
				str[j] = ft_substr(s, i, len);
				ft_free(str, j);
				j++;
			}
			i += len;
		}
		else
			i++;
	}
	str[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		nbr_words;

	nbr_words = count_words(s, c);
	str = malloc(sizeof(char *) * (nbr_words + 1));
	ft_remplir(str, s, nbr_words, c);
	return (str);
}
