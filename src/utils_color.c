/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:39:07 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/02 20:41:11 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_int(int r, int g, int b)
{
	return ((r & 0xFF) << 16 | (g & 0xFF) << 8 | (b & 0xFF));
}

static int	parse_rgb_triplet(char **p, int *r, int *g, int *b)
{
	char	*tmp;
	int		i;

	*r = ft_atoi(*p);
	tmp = ft_strchr(*p, ',');
	if (!tmp)
		return (-1);
	*g = ft_atoi(tmp + 1);
	tmp = ft_strchr(tmp + 1, ',');
	if (!tmp)
		return (-1);
	*b = ft_atoi(tmp + 1);
	i = 0;
	while ((*p)[i] && (*p)[i] != '\n')
	{
		if ((*p)[i] != ' ' && (*p)[i] != '\t' &&
			(*p)[i] != ',' && !ft_isdigit((*p)[i]))
			return (-1);
		i++;
	}
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (-1);
	return (0);
}

int	parse_color(const char *s, t_color *out)
{
	int		r;
	int		g;
	int		b;
	char	*p;

	p = (char *)s;
	while (*p == ' ' || *p == '\t')
		p++;
	if (parse_rgb_triplet(&p, &r, &g, &b) != 0)
		return (ft_putendl_fd("Error\nInvalid color", 2), -1);
	out->r = r;
	out->g = g;
	out->b = b;
	out->value = rgb_to_int(r, g, b);
	out->set = 1;
	return (0);
}
