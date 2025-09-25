/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:02:34 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/16 21:02:36 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_body_char(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	set_player_values(t_player *pl, t_dirplane dp)
{
	pl->dirx = dp.dirx;
	pl->diry = dp.diry;
	pl->planex = dp.planex;
	pl->planey = dp.planey;
}

void	set_player_dir(t_player *pl, char c)
{
	if (c == 'N')
		set_player_values(pl, (t_dirplane){0, -1, 0.66, 0});
	else if (c == 'S')
		set_player_values(pl, (t_dirplane){0, 1, -0.66, 0});
	else if (c == 'E')
		set_player_values(pl, (t_dirplane){1, 0, 0, 0.66});
	else if (c == 'W')
		set_player_values(pl, (t_dirplane){-1, 0, 0, -0.66});
}
