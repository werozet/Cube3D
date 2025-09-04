/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:36:52 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/04 16:29:23 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_map *m)
{
	int	y;

	if (!m || !m->grid)
		return ;
	y = 0;
	while (y < m->h)
	{
		free(m->grid[y]);
		y++;
	}
	free(m->grid);
	m->grid = NULL;
}

void	free_cfg(t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cfg->tex[i].img.img)
			mlx_destroy_image(NULL, cfg->tex[i].img.img);
		if (cfg->tex[i].path)
			free(cfg->tex[i].path);
		i++;
	}
	free_map(&cfg->map);
}

void	error_exit(const char *msg)
{
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}
