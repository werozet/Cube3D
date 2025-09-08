/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:39:29 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 14:14:33 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	copy_prefix(char *padded, const char *row, int *i)
{
	while (row[*i] && row[*i] != '\n')
	{
		padded[*i] = row[*i];
		(*i)++;
	}
}

static void	fill_spaces_tail(char *padded, int *i, int maxw)
{
	while (*i < maxw)
	{
		padded[*i] = ' ';
		(*i)++;
	}
}

static void	pad_row(char **prow, int maxw)
{
	char	*row;
	char	*padded;
	int		i;
	int		len;

	row = *prow;
	len = (int)ft_strlen(row);
	if (len >= maxw)
	{
		row[maxw] = 0;
		return ;
	}
	padded = (char *)malloc(maxw + 1);
	if (!padded)
		return ;
	i = 0;
	copy_prefix(padded, row, &i);
	fill_spaces_tail(padded, &i, maxw);
	padded[i] = 0;
	free(row);
	*prow = padded;
}

static void	pad_and_sanitize(t_map *m, int maxw)
{
	int		y;

	m->w = maxw;
	y = 0;
	while (y < m->h)
	{
		pad_row(&m->grid[y], maxw);
		sanitize_row(m->grid[y], maxw);
		y++;
	}
}

void	assign_and_pad(t_cfg *cfg, t_rows *rs)
{
	int	y;

	cfg->map.h = rs->h;
	cfg->map.w = rs->maxw;
	cfg->map.grid = malloc(sizeof(char *) * cfg->map.h);
	if (!cfg->map.grid)
		error_exit("alloc map grid");
	y = 0;
	while (y < cfg->map.h)
	{
		cfg->map.grid[y] = malloc(cfg->map.w + 1);
		if (!cfg->map.grid[y])
		{
			cfg->map.h = y;  // Set height to number of successfully allocated rows
			free_map(&cfg->map);
			error_exit("alloc map row");
		}
		fill_row(cfg->map.grid[y], rs->rows[y], cfg->map.w);
		y++;
	}
	pad_and_sanitize(&cfg->map, rs->maxw);
}
