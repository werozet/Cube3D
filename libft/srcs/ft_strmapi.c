/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:24:53 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/11 18:56:02 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*mapped_str;

	i = 0;
	len = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	while (s[len] != '\0')
	{
		len++;
	}
	mapped_str = (char *)malloc(len + 1);
	if (mapped_str == NULL)
		return (NULL);
	while (i < len)
	{
		mapped_str[i] = f(i, s[i]);
		i++;
	}
	mapped_str[len] = '\0';
	return (mapped_str);
}
