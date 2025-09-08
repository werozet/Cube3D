/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:39:01 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:45 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	select_tex(int side, double rdx, double rdy)
{
	if (side == 0)
	{
		if (rdx > 0.0)
			return (2);
		return (3);
	}
	if (rdy > 0.0)
		return (0);
	return (1);
}

static void	run_dda(t_app *a, t_rc *r)
{
	while (r->hit == 0
		&& r->mapx >= 0 && r->mapy >= 0
		&& r->mapx < a->cfg.map.w && r->mapy < a->cfg.map.h)
	{
		if (r->sdistx < r->sdisty)
		{
			r->sdistx += r->sdx;
			r->mapx += r->stepx;
			r->side = 0;
		}
		else
		{
			r->sdisty += r->sdy;
			r->mapy += r->stepy;
			r->side = 1;
		}
		if (a->cfg.map.grid[r->mapy][r->mapx] == '1')
			r->hit = 1;
	}
}

static void	compute_perp_and_wallx(t_app *a, t_rc *r)
{
	if (r->side == 0)
		r->perp = (r->mapx - a->pl.x + (1 - r->stepx) / 2.0) / r->rdx;
	else
		r->perp = (r->mapy - a->pl.y + (1 - r->stepy) / 2.0) / r->rdy;
	if (r->perp < 1e-6)
		r->perp = 1e-6;
	if (r->side == 0)
		r->wall_x = a->pl.y + r->perp * r->rdy;
	else
		r->wall_x = a->pl.x + r->perp * r->rdx;
	r->wall_x = r->wall_x - floor(r->wall_x);
}

static void	draw_column(t_app *a, t_draw *d)
{
	int	tx;

	tx = compute_tx(a, d);
	draw_ceil_strip(a, d);
	draw_wall_strip(a, d, tx);
	draw_floor_strip(a, d);
}

void	render_frame(t_app *a)
{
	int		x;
	t_rc	r;
	t_draw	d;

	img_clear(&a->mlx.frame, 0);
	x = 0;
	while (x < WIN_W)
	{
		init_ray(a, x, &r);
		run_dda(a, &r);
		compute_perp_and_wallx(a, &r);
		build_draw_params(x, &r, &d);
		draw_column(a, &d);
		x++;
	}
	mlx_put_image_to_window(a->mlx.mlx, a->mlx.win, a->mlx.frame.img, 0, 0);
}
