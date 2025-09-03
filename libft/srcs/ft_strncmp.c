/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:03:04 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/05 12:46:09 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	while (str1 && str2 && n > 0)
	{
		if (*str1 != *str2)
		{
			return ((int)(*str1) - (int)(*str2));
		}
		str1++;
		str2++;
		n--;
	}
	return (0);
}
