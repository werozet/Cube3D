/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:39:04 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:48 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_mlx *m, t_cfg *cfg)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (!cfg->tex[i].path)
			return (ft_putendl_fd("Error\nMissing texture path", 2), -1);
		cfg->tex[i].img.img = mlx_xpm_file_to_image(m->mlx, cfg->tex[i].path,
				&cfg->tex[i].img.w, &cfg->tex[i].img.h);
		if (!cfg->tex[i].img.img)
			return (perror("mlx_xpm_file_to_image"), -1);
		cfg->tex[i].img.data = (int *)mlx_get_data_addr(cfg->tex[i].img.img,
				&cfg->tex[i].img.bpp, &cfg->tex[i].img.line_len,
				&cfg->tex[i].img.endian);
		cfg->tex[i].loaded = 1;
		i++;
	}
	if (!cfg->floor_col.set || !cfg->ceil_col.set)
		return (ft_putendl_fd("Error\nMissing colors", 2), -1);
	return (0);
}
