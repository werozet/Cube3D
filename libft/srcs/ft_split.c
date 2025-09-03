/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:28:46 by pmamala           #+#    #+#             */
/*   Updated: 2024/03/17 20:28:35 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_cont_substrings( char const *ptr, char c)
{
	size_t	num_substrings;

	num_substrings = 0;
	while (*ptr != '\0')
	{
		if (*ptr != c)
		{
			num_substrings++;
			while (*ptr != c && *ptr != '\0')
				ptr++;
		}
		else
			ptr++;
	}
	return (num_substrings);
}

static char	**ft_allocate_mem(size_t num_substrings)
{
	char	**result;

	result = (char **)malloc((num_substrings + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	return (result);
}

char	*ft_allocate_row(char *row_ptr, size_t len)
{
	row_ptr = (char *)malloc((len + 1) * sizeof(char));
	if (row_ptr == NULL)
	{
		free(row_ptr);
		return (NULL);
	}
	return (row_ptr);
}

void	ft_make_row(char **result, const char *ptr, const char *start, size_t i)
{
	size_t	len;

	len = ptr - start;
	result[i] = ft_allocate_row(result[i], len);
	ft_strlcpy(result[i], start, len + 1);
	result[i][len] = '\0';
}

char	**ft_split(char const *s, char c)
{
	size_t		num_substrings;
	char		**result;
	size_t		i;
	const char	*start;

	if (s == NULL)
		return (NULL);
	num_substrings = ft_cont_substrings(s, c);
	result = ft_allocate_mem(num_substrings);
	i = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			start = s;
			while (*s != c && *s != '\0')
				s++;
			ft_make_row(result, s, start, i);
			i++;
		}
		else
			s++;
	}
	result[num_substrings] = (NULL);
	return (result);
}
