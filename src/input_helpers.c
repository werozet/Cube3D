/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:19:05 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/04 16:29:36 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	dt_seconds(void)
{
	static struct timeval	prev = {0, 0};
	struct timeval			now;
	double					dt;

	gettimeofday(&now, NULL);
	if (prev.tv_sec == 0 && prev.tv_usec == 0)
		prev = now;
	dt = (now.tv_sec - prev.tv_sec) + (now.tv_usec - prev.tv_usec) / 1e6;
	prev = now;
	return (dt);
}

static void	try_move_xy(t_app *a, double nx, double ny)
{
	if (!is_wall(a, nx, a->pl.y))
		a->pl.x = nx;
	if (!is_wall(a, a->pl.x, ny))
		a->pl.y = ny;
}

static void	move_along(t_app *a, double vx, double vy, double ms)
{
	try_move_xy(a, a->pl.x + vx * ms, a->pl.y + vy * ms);
}

static void	rotate_player(t_app *a, double ang)
{
	double	c;
	double	s;
	double	old;

	c = cos(ang);
	s = sin(ang);
	old = a->pl.dirx;
	a->pl.dirx = a->pl.dirx * c - a->pl.diry * s;
	a->pl.diry = old * s + a->pl.diry * c;
	old = a->pl.planex;
	a->pl.planex = a->pl.planex * c - a->pl.planey * s;
	a->pl.planey = old * s + a->pl.planey * c;
}

void	move_player(t_app *a, double dt)
{
	double	ms;
	double	rs;
	double	ang;

	ms = a->move_speed * dt;
	rs = a->rot_speed * dt;
	if (a->keys.w)
		move_along(a, a->pl.dirx, a->pl.diry, ms);
	if (a->keys.s)
		move_along(a, -a->pl.dirx, -a->pl.diry, ms);
	if (a->keys.a)
		move_along(a, -a->pl.planex, -a->pl.planey, ms);
	if (a->keys.d)
		move_along(a, a->pl.planex, a->pl.planey, ms);
	ang = 0.0;
	if (a->keys.left)
		ang = ang - rs;
	if (a->keys.right)
		ang = ang + rs;
	if (ang != 0.0)
		rotate_player(a, ang);
}
