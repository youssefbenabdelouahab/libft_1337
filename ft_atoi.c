/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-abd <yben-abd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 19:26:10 by yben-abd          #+#    #+#             */
/*   Updated: 2026/10/21 14:05:15 by yben-abd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (res > (9223372036854775807 - (*str - '0')) / 10)
		{
			if (sign == 1)
				return (-1);
			else if (sign == -1)
				return (0);
		}
		res = res * 10 + (*str - '0');
		str++;
	}
	return ((int)(res * sign));
}
