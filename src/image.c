/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:38:50 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/02 19:36:16 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	img_create(t_mlx *m, t_img *img, int w, int h)
{
	img->img = mlx_new_image(m->mlx, w, h);
	if (!img->img)
		return (-1);
	img->data = (int *)mlx_get_data_addr(img->img,
			&img->bpp, &img->line_len, &img->endian);
	img->w = w;
	img->h = h;
	return (0);
}

void	img_clear(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			img_put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	img_put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dst = (char *)img->data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}
