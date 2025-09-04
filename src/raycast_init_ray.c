/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init_ray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 22:15:36 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/04 16:29:53 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	build_draw_params(int x, t_rc *r, t_draw *d)
{
	int	line_h;

	line_h = (int)(WIN_H / r->perp);
	d->draw_start = -line_h / 2 + WIN_H / 2;
	d->draw_end = line_h / 2 + WIN_H / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	if (d->draw_end >= WIN_H)
		d->draw_end = WIN_H - 1;
	d->x = x;
	d->side = r->side;
	d->tex_id = select_tex(r->side, r->rdx, r->rdy);
	d->wall_x = r->wall_x;
}

static void	init_side_dist(t_app *a, t_rc *r)
{
	if (r->rdx < 0.0)
		r->sdistx = (a->pl.x - r->mapx) * r->sdx;
	else
		r->sdistx = (r->mapx + 1.0 - a->pl.x) * r->sdx;
	if (r->rdy < 0.0)
		r->sdisty = (a->pl.y - r->mapy) * r->sdy;
	else
		r->sdisty = (r->mapy + 1.0 - a->pl.y) * r->sdy;
}

static void	set_steps(t_rc *r)
{
	if (r->rdx < 0.0)
		r->stepx = -1;
	else
		r->stepx = 1;
	if (r->rdy < 0.0)
		r->stepy = -1;
	else
		r->stepy = 1;
}

static void	compute_inv_deltas(t_rc *r)
{
	if (r->rdx == 0.0)
		r->sdx = 1e30;
	else
		r->sdx = fabs(1.0 / r->rdx);
	if (r->rdy == 0.0)
		r->sdy = 1e30;
	else
		r->sdy = fabs(1.0 / r->rdy);
}

void	init_ray(t_app *a, int x, t_rc *r)
{
	r->camx = (2.0 * x / (double)WIN_W) - 1.0;
	r->rdx = a->pl.dirx + a->pl.planex * r->camx;
	r->rdy = a->pl.diry + a->pl.planey * r->camx;
	r->mapx = (int)a->pl.x;
	r->mapy = (int)a->pl.y;
	compute_inv_deltas(r);
	set_steps(r);
	init_side_dist(a, r);
	r->side = 0;
	r->hit = 0;
}
