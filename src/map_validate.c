/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:38:59 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/04 16:29:50 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_void(char c)
{
	return (c == ' ');
}

static int	is_inside(t_map *m, t_point p)
{
	if (p.x < 0 || p.y < 0)
		return (0);
	if (p.x >= m->w || p.y >= m->h)
		return (0);
	if (is_void(m->grid[p.y][p.x]))
		return (0);
	return (1);
}

static int	check_cell(t_map *m, t_point p)
{
	t_point	r;
	t_point	l;
	t_point	u;
	t_point	d;

	if (m->grid[p.y][p.x] != '0')
		return (0);
	r.x = p.x + 1;
	r.y = p.y;
	if (!is_inside(m, r))
		return (-1);
	l.x = p.x - 1;
	l.y = p.y;
	if (!is_inside(m, l))
		return (-1);
	u.x = p.x;
	u.y = p.y + 1;
	if (!is_inside(m, u))
		return (-1);
	d.x = p.x;
	d.y = p.y - 1;
	if (!is_inside(m, d))
		return (-1);
	return (0);
}

int	validate_map(t_map *m)
{
	int		x;
	int		y;
	t_point	p;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			p.x = x;
			p.y = y;
			if (m->grid[y][x] == '0' && check_cell(m, p) != 0)
			{
				ft_putendl_fd("Error\nMap not closed by walls", 2);
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
