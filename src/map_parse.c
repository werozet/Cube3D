/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:38:56 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/02 22:06:48 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_body_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	process_cell(t_cfg *cfg, t_player *pl, int *px_set, t_point p)
{
	char	c;

	c = cfg->map.grid[p.y][p.x];
	if (!is_valid_body_char(c))
	{
		ft_putendl_fd("Error\nInvalid map char", 2);
		return (-1);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		*px_set = *px_set + 1;
		if (*px_set > 1)
		{
			ft_putendl_fd("Error\nMultiple player spawns", 2);
			return (-1);
		}
		pl->x = p.x + 0.5;
		pl->y = p.y + 0.5;
		cfg->map.grid[p.y][p.x] = '0';
	}
	return (0);
}

static int	scan_map_for_player(t_cfg *cfg, t_player *pl, int *px_set)
{
	int	y;
	int	x;

	y = 0;
	while (y < cfg->map.h)
	{
		x = 0;
		while (x < cfg->map.w)
		{
			if (process_cell(cfg, pl, px_set, (t_point){x, y}) != 0)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

static int	scan_and_validate(t_cfg *cfg, t_player *pl)
{
	int	px_set;

	px_set = 0;
	if (scan_map_for_player(cfg, pl, &px_set) != 0)
		return (-1);
	if (!px_set)
	{
		ft_putendl_fd("Error\nNo player spawn", 2);
		return (-1);
	}
	if (validate_map(&cfg->map) != 0)
		return (-1);
	return (0);
}

int	parse_map_and_player(int fd, char *first_map_line, t_cfg *cfg, t_player *pl)
{
	t_rows	rs;

	if (read_all_rows(fd, first_map_line, &rs) != 0)
		return (-1);
	assign_and_pad(cfg, &rs);
	if (scan_and_validate(cfg, pl) != 0)
		return (-1);
	return (0);
}
