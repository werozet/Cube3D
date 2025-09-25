/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:25:29 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/11 13:55:15 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub_extension(const char *filename)
{
	int	len;
	int	i;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	i = len - 4;
	if (filename[i] == '.' && filename[i + 1] == 'c'
		&& filename[i + 2] == 'u' && filename[i + 3] == 'b')
		return (1);
	return (0);
}

void	validate_args_or_die(int argc, char **argv)
{
	if (argc != 2)
		error_exit("Error\nUsage: ./cub3D <map.cub>");
	if (!has_cub_extension(argv[1]))
		error_exit("Error\nMap file must have .cub extension");
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
