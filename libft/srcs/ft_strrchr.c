/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 16:09:52 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/18 13:12:41 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char *ft_strrchr(const char *str, int c)
{
    i;

    i = ft_strlen(str);
    while (i >= 0)
    {
        if(str[i] == c)
        {
            return ((char *)(str + i));
        }
        i--;
    }
    return NULL;
    
}
*/
char
	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}
