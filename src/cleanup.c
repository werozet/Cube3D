/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:36:52 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:22:56 by wzielins         ###   ########.fr       */
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
		free(cfg->tex[i].path);
		cfg->tex[i].path = NULL;
		i++;
	}
	free_map(&cfg->map);
}

void	error_exit(const char *msg)
{
	ft_putendl_fd((char *)msg, 2);
	exit(1);
}

void	destroy_mlx_and_assets(t_app *app)
{
	destroy_textures(app);
	if (app->mlx.frame.img)
	{
		mlx_destroy_image(app->mlx.mlx, app->mlx.frame.img);
		app->mlx.frame.img = NULL;
	}
	if (app->mlx.win)
	{
		mlx_destroy_window(app->mlx.mlx, app->mlx.win);
		app->mlx.win = NULL;
	}
	if (app->mlx.mlx)
		mlx_destroy_display(app->mlx.mlx);
	if (app->mlx.mlx)
	{
		free(app->mlx.mlx);
		app->mlx.mlx = NULL;
	}
}

void	free_rows(t_rows *r)
{
	int	i;

	if (!r || !r->rows)
		return ;
	i = 0;
	while (i < r->h)
	{
		free(r->rows[i]);
		r->rows[i] = NULL;
		i++;
	}
	free(r->rows);
	r->rows = NULL;
	r->h = 0;
	r->maxw = 0;
}
