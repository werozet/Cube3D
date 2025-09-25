/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parse_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wzielins <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 21:03:07 by pmamala           #+#    #+#             */
/*   Updated: 2025/09/11 13:53:07 by wzielins         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_line(const char *s)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	while (s[i])
	{
		if (s[i] == '0' || s[i] == '1' || s[i] == ' '
			|| s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
			has_digit = 1;
		else if (s[i] != '\n' && s[i] != '\t')
			return (0);
		i++;
	}
	return (has_digit);
}

char	*gnl(int fd)
{
	char	buf[1];
	char	*line;
	char	*tmp;
	int		r;
	char	add[2];

	line = NULL;
	while (1)
	{
		r = read(fd, buf, 1);
		if (r <= 0)
			break ;
		add[0] = buf[0];
		add[1] = '\0';
		if (line)
			tmp = ft_strjoin(line, add);
		else
			tmp = ft_strjoin("", add);
		if (line)
			free(line);
		line = tmp;
		if (buf[0] == '\n')
			break ;
	}
	return (line);
}

static int	handle_map_line(int fd, char *line, t_cfg *cfg, t_player *pl)
{
	int	ret;

	ret = parse_map_and_player(fd, line, cfg, pl);
	free(line);
	if (ret != 0)
		return (-1);
	return (1);
}

static int	handle_ident_line(char *line, t_cfg *cfg)
{
	int	ret;

	ret = parse_ident_line(line, cfg);
	free(line);
	if (ret != 0)
		return (-1);
	return (0);
}

int	handle_line(char *line, int fd, t_cfg *cfg, t_player *pl)
{
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return (0);
	}
	if (is_map_line(line))
		return (handle_map_line(fd, line, cfg, pl));
	return (handle_ident_line(line, cfg));
}
