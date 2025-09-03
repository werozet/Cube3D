/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:15:33 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/02 22:58:26 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tex_color(t_tex *t, int tx, int ty)
{
	int	*data;
	int	w;
	int	sl;

	if (!t->loaded || !t->img.img)
		return (0x00FF00);
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	if (tx >= t->img.w)
		tx = t->img.w - 1;
	if (ty >= t->img.h)
		ty = t->img.h - 1;
	w = t->img.w;
	sl = t->img.line_len / 4;
	(void)w;
	data = t->img.data;
	return (data[ty * sl + tx]);
}

int	compute_tx(t_app *a, t_draw *d)
{
	int	tx;
	int	w;

	w = a->cfg.tex[d->tex_id].img.w;
	tx = (int)(d->wall_x * (double)w);
	if (d->side == 0 && a->pl.dirx > 0.0)
		tx = w - tx - 1;
	if (d->side == 1 && a->pl.diry < 0.0)
		tx = w - tx - 1;
	return (tx);
}

void	draw_ceil_strip(t_app *a, t_draw *d)
{
	int	y;

	y = 0;
	while (y < d->draw_start)
	{
		img_put_pixel(&a->mlx.frame, d->x, y, a->cfg.ceil_col.value);
		y++;
	}
}

void	draw_wall_strip(t_app *a, t_draw *d, int tx)
{
	double	step;
	double	tex_pos;
	int		y;
	int		ty;
	int		th;

	th = a->cfg.tex[d->tex_id].img.h;
	step = (1.0 * th) / (double)(d->draw_end - d->draw_start);
	tex_pos = (d->draw_start - WIN_H / 2
			+ (d->draw_end - d->draw_start) / 2.0) * step;
	y = d->draw_start;
	while (y < d->draw_end)
	{
		ty = (int)tex_pos & (th - 1);
		tex_pos += step;
		img_put_pixel(&a->mlx.frame, d->x, y,
			get_tex_color(&a->cfg.tex[d->tex_id], tx, ty));
		y++;
	}
}

void	draw_floor_strip(t_app *a, t_draw *d)
{
	int	y;

	y = d->draw_end;
	while (y < WIN_H)
	{
		img_put_pixel(&a->mlx.frame, d->x, y, a->cfg.floor_col.value);
		y++;
	}
}
