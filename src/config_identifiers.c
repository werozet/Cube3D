/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_identifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:37:07 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/08 13:23:07 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_xpm_and_open(const char *path, size_t len)
{
	int	fd;

	if (len < 4 || ft_strncmp(path + (len - 4), ".xpm", 4) != 0)
	{
		ft_putendl_fd("Error\nTexture must be .xpm", 2);
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error\nCannot open texture: ", 2);
		ft_putendl_fd((char *)path, 2);
		return (0);
	}
	close(fd);
	return (1);
}

static int	assign_path(t_tex *t, char *path)
{
	if (t->path)
		free(t->path);
	t->path = path;
	return (0);
}

static char	*dup_trimmed(const char *p, size_t len)
{
	char	*out;

	out = malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, p, len);
	out[len] = '\0';
	return (out);
}

int	set_path(t_tex *t, char *p)
{
	size_t	len;
	char	*path;

	if (!t || !p)
		return (ft_putendl_fd((char *)"Error\nInvalid args to setPath", 2), -1);
	if (t->path)
		return (dup_tex_key());
	p = skip_spaces(p);
	if (!*p)
		return (ft_putendl_fd((char *)"Error\nMissing texture path", 2), -1);
	len = get_trimmed_len(p);
	if (!len)
		return (ft_putendl_fd((char *)"Error\nMissing texture path", 2), -1);
	path = dup_trimmed(p, len);
	if (!path)
		return (-1);
	if (!check_xpm_and_open(path, len))
		return (free(path), -1);
	return (assign_path(t, path));
}

int	parse_ident_line(char *line, t_cfg *cfg)
{
	char	*s;

	s = skip_spaces(line);
	if (!ft_strncmp(s, "NO", 2) && (s[2] == ' ' || s[2] == '\t'))
		return (set_path(&cfg->tex[0], s + 3));
	if (!ft_strncmp(s, "SO", 2) && (s[2] == ' ' || s[2] == '\t'))
		return (set_path(&cfg->tex[1], s + 3));
	if (!ft_strncmp(s, "WE", 2) && (s[2] == ' ' || s[2] == '\t'))
		return (set_path(&cfg->tex[2], s + 3));
	if (!ft_strncmp(s, "EA", 2) && (s[2] == ' ' || s[2] == '\t'))
		return (set_path(&cfg->tex[3], s + 3));
	if (s[0] == 'F' && (s[1] == ' ' || s[1] == '\t'))
	{
		if (cfg->floor_col.set)
			return (dup_color_key());
		return (parse_color(s + 2, &cfg->floor_col));
	}
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
	{
		if (cfg->ceil_col.set)
			return (dup_color_key());
		return (parse_color(s + 2, &cfg->ceil_col));
	}
	ft_putendl_fd((char *)"Error\nUnknown identifier", 2);
	return (-1);
}
