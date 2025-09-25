/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:39:07 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:51 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_ws(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

static int	parse_u8_comp(char **ps, int *out)
{
	long	val;
	char	*s;

	s = skip_ws(*ps);
	if (!ft_isdigit(*s))
		return (-1);
	val = 0;
	while (ft_isdigit(*s))
	{
		val = val * 10 + (*s - '0');
		if (val > 255)
			return (-1);
		s++;
	}
	*out = (int)val;
	*ps = s;
	return (0);
}

static int	expect_comma(char **ps)
{
	char	*s;

	s = skip_ws(*ps);
	if (*s != ',')
		return (-1);
	*ps = s + 1;
	return (0);
}

static int	parse_rgb_triplet(char **p, int *r, int *g, int *b)
{
	char	*s;

	if (parse_u8_comp(p, r) != 0)
		return (-1);
	if (expect_comma(p) != 0 || parse_u8_comp(p, g) != 0)
		return (-1);
	if (expect_comma(p) != 0 || parse_u8_comp(p, b) != 0)
		return (-1);
	s = skip_ws(*p);
	if (*s != '\0' && *s != '\n')
		return (-1);
	*p = s;
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
