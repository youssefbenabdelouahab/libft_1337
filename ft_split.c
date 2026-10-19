/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 13:59:25 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/19 21:23:13 by yben-abd         ###   ########.fr       */
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
	while (i < x)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

static	int	ft_remplir(char **str, char const *s, char c)
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
			str[j] = ft_substr(s, i, len);
			if (!str[j])
			{
				ft_free(str, j);
				return (0);
			}
			j++;
			i += len;
		}
		else
			i++;
	}
	str[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		nbr_words;

	if (s == NULL)
		return (NULL);
	nbr_words = count_words(s, c);
	str = malloc(sizeof(char *) * (nbr_words + 1));
	if (str == NULL)
		return (NULL);
	if (!ft_remplir(str, s, c))
		return (NULL);
	return (str);
}
