/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:45:45 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:33 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sanitize_row(char *row, int maxw)
{
	int	x;

	x = 0;
	while (x < maxw)
	{
		if (row[x] == '\n')
			row[x] = ' ';
		x++;
	}
}

void	destroy_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (app->cfg.tex[i].img.img)
		{
			mlx_destroy_image(app->mlx.mlx, app->cfg.tex[i].img.img);
			app->cfg.tex[i].img.img = NULL;
		}
		i++;
	}
}
