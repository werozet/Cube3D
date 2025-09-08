/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:38:52 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:21 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop(t_app *app)
{
	double	dt;

	dt = dt_seconds();
	move_player(app, dt);
	render_frame(app);
	return (0);
}

int	on_key_press(int key, t_app *a)
{
	if (key == K_ESC)
		on_destroy(a);
	if (key == K_W)
		a->keys.w = 1;
	if (key == K_A)
		a->keys.a = 1;
	if (key == K_S)
		a->keys.s = 1;
	if (key == K_D)
		a->keys.d = 1;
	if (key == K_LEFT)
		a->keys.left = 1;
	if (key == K_RIGHT)
		a->keys.right = 1;
	return (0);
}

int	on_key_release(int key, t_app *a)
{
	if (key == K_W)
		a->keys.w = 0;
	if (key == K_A)
		a->keys.a = 0;
	if (key == K_S)
		a->keys.s = 0;
	if (key == K_D)
		a->keys.d = 0;
	if (key == K_LEFT)
		a->keys.left = 0;
	if (key == K_RIGHT)
		a->keys.right = 0;
	return (0);
}

int	on_destroy(t_app *a)
{
	destroy_mlx_and_assets(a);
	free_cfg(&a->cfg);
	exit(0);
	return (0);
}

int	is_wall(t_app *a, double nx, double ny)
{
	int	x;
	int	y;

	x = (int)nx;
	y = (int)ny;
	if (x < 0 || y < 0 || x >= a->cfg.map.w || y >= a->cfg.map.h)
		return (1);
	return (a->cfg.map.grid[y][x] == '1');
}
