/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:13:54 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/17 19:42:48 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	num;

	num = 0;
	sign = 1;
	while (*str <= 32 && *str > 0)
	{
		if (*str == '\e')
			return (0);
		++str;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		num *= 10;
		num += (*str - 48);
		++str;
	}
	num *= sign;
	return (num);
}
