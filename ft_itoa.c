/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 20:44:47 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/18 14:00:54 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_len(int n)
{
	int		i;
	long	nbr;

	i = 1;
	nbr = n;
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 9)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	ft_putnb_atoi(int n, char *s1)
{
	long	div;
	long	nbr;
	char	c;
	int		i;

	nbr = n;
	i = 0;
	if (nbr < 0)
	{
		s1[i] = '-';
		nbr = -nbr;
		i++;
	}
	div = 1;
	while (nbr / div > 9)
		div *= 10;
	while (div > 0)
	{
		c = (nbr / div) + '0';
		s1[i++] = c;
		nbr %= div;
		div /= 10;
	}
	s1[i] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*s1;

	len = cal_len(n) + 1;
	if (n < 0)
		len += 1;
	s1 = malloc(len);
	if (s1 == NULL)
		return (NULL);
	ft_putnb_atoi(n, s1);
	return (s1);
}
