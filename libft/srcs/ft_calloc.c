/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:49:09 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/17 19:50:11 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dst;

	if (count > SIZE_MAX / size)
		return (0);
	dst = (void *)malloc(count * size);
	if (!dst)
		return (NULL);
	ft_memset(dst, 0, count * size);
	return (dst);
}
