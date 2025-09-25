/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_identifiers_helper.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:18:34 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/11 16:18:38 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

size_t	get_trimmed_len(const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	while (len && (s[len - 1] == '\n' || s[len - 1] == ' '
			|| s[len - 1] == '\t' || s[len - 1] == '\r'))
		len--;
	return (len);
}

int	dup_tex_key(void)
{
	ft_putendl_fd((char *)"Error\nDuplicate texture key", 2);
	return (-1);
}

int	dup_color_key(void)
{
	ft_putendl_fd((char *)"Error\nDuplicate color key", 2);
	return (-1);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}
