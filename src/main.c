/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmamala <pmamala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:16:41 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/02 21:29:18 by pmamala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_app_or_die(t_app *app, const char *path)
{
	ft_bzero(app, sizeof(*app));
	if (parse_config(path, &app->cfg, &app->pl) != 0)
		error_exit("Error\nInvalid configuration");
	init_player_plane(&app->pl, 'N');
	setup_app_defaults(app);
}

static void	init_mlx_or_die(t_app *app)
{
	app->mlx.mlx = mlx_init();
	if (!app->mlx.mlx)
		error_exit("Error\nmlx_init failed");
	app->mlx.win = mlx_new_window(app->mlx.mlx, WIN_W, WIN_H, "cub3D");
	if (!app->mlx.win)
		error_exit("Error\nmlx_new_window failed");
	if (img_create(&app->mlx, &app->mlx.frame, WIN_W, WIN_H) != 0)
		error_exit("Error\nimage allocation failed");
}

static void	load_assets_or_die(t_app *app)
{
	if (load_textures(&app->mlx, &app->cfg) != 0)
		error_exit("Error\ntexture load failed");
}

static void	install_hooks(t_app *app)
{
	mlx_hook(app->mlx.win, EV_KEYPRESS, 1L << 0, on_key_press, app);
	mlx_hook(app->mlx.win, EV_KEYRELEASE, 1L << 1, on_key_release, app);
	mlx_hook(app->mlx.win, EV_DESTROY, 1L << 17, on_destroy, app);
	mlx_loop_hook(app->mlx.mlx, game_loop, app);
}

int	main(int argc, char **argv)
{
	t_app	app;

	validate_args_or_die(argc);
	init_app_or_die(&app, argv[1]);
	init_mlx_or_die(&app);
	load_assets_or_die(&app);
	install_hooks(&app);
	mlx_loop(app.mlx.mlx);
	free_cfg(&app.cfg);
	return (0);
}
