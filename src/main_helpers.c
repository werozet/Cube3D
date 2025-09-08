/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:25:29 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:24 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_args_or_die(int argc)
{
	if (argc != 2)
		error_exit("Error\nUsage: ./cub3D <map.cub>");
}

static void	set_dir_plane(t_player *pl, t_vec2 dir, t_vec2 plane)
{
	pl->dirx = dir.x;
	pl->diry = dir.y;
	pl->planex = plane.x;
	pl->planey = plane.y;
}

void	init_player_plane(t_player *pl, char orient)
{
	if (orient == 'N')
		set_dir_plane(pl, (t_vec2){0.0, -1.0}, (t_vec2){0.66, 0.0});
	else if (orient == 'S')
		set_dir_plane(pl, (t_vec2){0.0, 1.0}, (t_vec2){-0.66, 0.0});
	else if (orient == 'E')
		set_dir_plane(pl, (t_vec2){1.0, 0.0}, (t_vec2){0.0, 0.66});
	else
		set_dir_plane(pl, (t_vec2){-1.0, 0.0}, (t_vec2){0.0, -0.66});
}

void	setup_app_defaults(t_app *app)
{
	app->keys.w = 0;
	app->keys.a = 0;
	app->keys.s = 0;
	app->keys.d = 0;
	app->keys.left = 0;
	app->keys.right = 0;
	app->running = 1;
	app->move_speed = 3.0;
	app->rot_speed = 2.0;
}
