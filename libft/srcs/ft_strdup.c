/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:09:07 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/17 19:55:01 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*duplicate;

	if (str == NULL)
	{
		return (NULL);
	}
	len = ft_strlen(str) + 1;
	duplicate = (char *)malloc(len * sizeof(char));
	if (duplicate == NULL)
	{
		return (NULL);
	}
	ft_strlcpy(duplicate, str, len);
	return (duplicate);
}
