/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:39:29 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/11 13:53:46 by wzielins         ###   ########.fr       */
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
	int		i;

	if (!prow || !*prow || maxw < 0)
		return ;
	row = *prow;
	i = 0;
	copy_prefix(row, row, &i);
	fill_spaces_tail(row, &i, maxw);
	row[i] = '\0';
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
		cfg->map.grid[y] = malloc((cfg->map.w + 1) * sizeof(char));
		if (!cfg->map.grid[y])
		{
			cfg->map.h = y;
			free_map(&cfg->map);
			error_exit("alloc map row");
		}
		fill_row(cfg->map.grid[y], rs->rows[y], cfg->map.w);
		y++;
	}
	pad_and_sanitize(&cfg->map, rs->maxw);
}
