/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_identifiers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:37:07 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/04 16:29:26 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

static int	set_path(t_tex *t, char *p)
{
	char	*path;

	p = skip_spaces(p);
	if (!*p)
		return (ft_putendl_fd("Error\nMissing texture path", 2), -1);
	path = ft_strdup(p);
	if (!path)
		return (-1);
	if (path[ft_strlen(path) - 1] == '\n')
		path[ft_strlen(path) - 1] = 0;
	if (t->path)
		free(t->path);
	t->path = path;
	return (0);
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
		return (parse_color(s + 2, &cfg->floor_col));
	if (s[0] == 'C' && (s[1] == ' ' || s[1] == '\t'))
		return (parse_color(s + 2, &cfg->ceil_col));
	return (ft_putendl_fd("Error\nUnknown identifier", 2), -1);
}
