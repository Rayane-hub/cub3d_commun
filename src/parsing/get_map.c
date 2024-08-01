/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:09 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/01 19:07:39 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_fill_map(t_data *data)
{
	char	*s1;
	char	*tmp_s1;
	char	*s2;

	tmp_s1 = malloc(1);
	if (!tmp_s1)
		return (-1);
	tmp_s1[0] = '\0';
	s2 = get_next_line(data->fd);
	if (!s2)
		return (printf("Error\nEmpty map\n"), free(tmp_s1), -1);
	while (s2)
	{
		s1 = ft_strjoin(tmp_s1, s2);
		if (!s1)
			return (printf("Error\nEmpty map\n"), free(tmp_s1), free(s2), -1);
		free(tmp_s1);
		tmp_s1 = s1;
		free(s2);
		s2 = get_next_line(data->fd);
	}
	data->map = ft_split(tmp_s1, '\n');
	free(tmp_s1);
	return (0);
}

int	ft_is_map_char_valid(t_data *data, char *s, int *nb_player, int y)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'O')
		{
			data->player.dir = s[i];
			data->player.pos_x = i;
			data->player.pos_y = y;
			*nb_player = *nb_player + 1;
		}
		if (s[i] != '1' && s[i] != '0' && s[i] != ' ' && s[i] != '\t' && \
			s[i] != 'N' && s[i] != 'S' && s[i] != 'W' && s[i] != 'O')
			return (printf("Error\nInvalid char in map |%c|\n", s[i]), -1);
		i++;
	}
	return (0);
}

int	ft_check_around_char(t_data *data, int i, int j)
{
	if (i == 0 && (data->map[i][j] != '1' && data->map[i][j] != ' '))
		return (printf("Error\nOpen map. Forbidden character at i == 0\n"), -1);
	if (j == 0 && (data->map[i][j] != '1' && data->map[i][j] != ' '))
		return (printf("Error\nOpen map. Forbidden character at j == 0\n"), -1);
	if (j > 0 && i > 0)
	{
		if (data->map[i][j] == '0' || data->map[i][j] == 'N' || \
		data->map[i][j] == 'S' || data->map[i][j] == 'O' || \
		data->map[i][j] == 'W')
		{
			if (data->map[i - 1][j] == ' ' || data->map[i - 1][j] == '\0')
				return (printf("Error\nOpen map. Char at up\n"), -1);
			if (data->map[i + 1][j] == ' ' || data->map[i + 1][j] == '\0')
				return (printf("Error\nOpen map. Char at down\n"), -1);
			if (data->map[i][j - 1] == ' ' || data->map[i][j - 1] == '\0')
				return (printf("Error\nOpen map. Char at left\n"), -1);
			if (data->map[i][j + 1] == ' ' || data->map[i][j + 1] == '\0')
				return (printf("Error\nOpen map. Char at right\n"), -1);
		}
	}
	return (0);
}

int	ft_is_map_enclosed_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (ft_check_around_char(data, i, j) != 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_get_map(t_data *data)
{
	int	i;
	int	nb_player;

	i = 0;
	nb_player = 0;
	if (ft_fill_map(data) != 0)
		return (-1);
	while (data->map[i])
	{
		if (ft_is_map_char_valid(data, data->map[i], &nb_player, i) != 0)
			return (-1);
		i++;
	}
	if (nb_player != 1)
		return (printf("Error\nIncorrect number of players\n"), -1);
	if (ft_is_map_enclosed_wall(data) != 0)
		return (-1);
	return (0);
}
