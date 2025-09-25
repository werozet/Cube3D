/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:31:47 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/10 14:37:53 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"

/* Window size */
# define WIN_W 1024
# define WIN_H 640

/* Keys (Linux) */
# define K_ESC 65307
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100
# define K_LEFT 65361
# define K_RIGHT 65363

/* Events */
# define EV_KEYPRESS 2
# define EV_KEYRELEASE 3
# define EV_DESTROY 17

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_rows
{
	char	**rows;
	int		h;
	int		maxw;
}			t_rows;

typedef struct s_dirplane
{
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}	t_dirplane;

typedef struct s_rc
{
	double	camx;
	double	rdx;
	double	rdy;
	int		mapx;
	int		mapy;
	double	sdx;
	double	sdy;
	int		stepx;
	int		stepy;
	double	sdistx;
	double	sdisty;
	int		side;
	int		hit;
	double	perp;
	double	wall_x;
}			t_rc;

typedef struct s_draw
{
	int		x;
	int		draw_start;
	int		draw_end;
	int		side;
	int		tex_id;
	double	wall_x;
}			t_draw;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}			t_img;

typedef struct s_tex
{
	char	*path;
	t_img	img;
	int		loaded;
}			t_tex;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		value;
	int		set;
}			t_color;

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
}			t_map;

typedef struct s_cfg
{
	t_tex	tex[4];
	t_color	floor_col;
	t_color	ceil_col;
	t_map	map;
}			t_cfg;

typedef struct s_keys
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		left;
	int		right;
}			t_keys;

typedef struct s_player
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
}			t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	frame;
}			t_mlx;

typedef struct s_app
{
	t_mlx		mlx;
	t_cfg		cfg;
	t_keys		keys;
	t_player	pl;
	int			running;
	double		move_speed;
	double		rot_speed;
}			t_app;

/* parsing */
int		handle_line(char *line, int fd, t_cfg *cfg, t_player *pl);
int		process_file(int fd, t_cfg *cfg, t_player *pl);
int		parse_config(const char *path, t_cfg *cfg, t_player *pl);
int		parse_ident_line(char *line, t_cfg *cfg);
int		parse_map_and_player(int fd, char *first_map_line,
			t_cfg *cfg, t_player *pl);
int		validate_map(t_map *map);
int		dup_tex_key(void);
int		dup_color_key(void);
char	*gnl(int fd);

/* utils - color */
int		parse_color(const char *s, t_color *out);
int		rgb_to_int(int r, int g, int b);

/* utils - math */
double	clamp(double v, double lo, double hi);

/* image */
int		img_create(t_mlx *m, t_img *img, int w, int h);
void	img_clear(t_img *img, int color);
void	img_put_pixel(t_img *img, int x, int y, int color);

/* textures / render */
int		load_textures(t_mlx *m, t_cfg *cfg);
void	render_frame(t_app *app);

/* input */
double	dt_seconds(void);
void	move_player(t_app *a, double dt);
int		on_key_press(int key, t_app *app);
int		on_key_release(int key, t_app *app);
int		on_destroy(t_app *app);
int		game_loop(t_app *app);
int		is_wall(t_app *a, double nx, double ny);

/* init helpers */
void	init_player_plane(t_player *pl, char orient);
void	setup_app_defaults(t_app *app);
void	validate_args_or_die(int argc, char **argv);

/* map helpers */
int		read_all_rows(int fd, char *first, t_rows *rs);
int		is_valid_body_char(char c);
void	assign_and_pad(t_cfg *cfg, t_rows *rs);
void	sanitize_row(char *row, int maxw);
void	set_player_dir(t_player *pl, char c);
void	set_player_values(t_player *pl, t_dirplane dp);

/* raycast helpers */
void	init_ray(t_app *a, int x, t_rc *r);
void	build_draw_params(int x, t_rc *r, t_draw *d);
int		compute_tx(t_app *a, t_draw *d);
void	draw_ceil_strip(t_app *a, t_draw *d);
void	draw_wall_strip(t_app *a, t_draw *d, int tx);
void	draw_floor_strip(t_app *a, t_draw *d);
int		select_tex(int side, double rdx, double rdy);

/* cleanup */
void	free_cfg(t_cfg *cfg);
void	free_map(t_map *m);
void	error_exit(const char *msg);
void	destroy_mlx_and_assets(t_app *app);
void	free_rows(t_rows *r);
void	fill_row(char *dst, const char *src, int w);
void	destroy_textures(t_app *app);
char	*skip_spaces(char *s);
size_t	get_trimmed_len(const char *s);

#endif
