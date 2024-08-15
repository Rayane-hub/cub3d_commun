/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:35:09 by rasamad           #+#    #+#             */
/*   Updated: 2024/08/15 13:36:56 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	ft_loop_fill_map(t_data *data, char *tmp_s1, char *s2)
{
	char	*s1;
	int check = 0;

	while (s2)
	{
		if (s2[0] == '\n')
			check = 1;
		else
		{
			if (check)
				return (printf("Error\nMap discontinuous\n"), free(s2), free(tmp_s1), -1);
			s1 = ft_strjoin(tmp_s1, s2);
			if (!s1)
				return (printf("Error\nMap empty\n"), free(tmp_s1), free(s2), -1);
			free(tmp_s1);
			tmp_s1 = s1;
		}
		free(s2);
		s2 = get_next_line(data->fd);
	}
	data->m = ft_split(tmp_s1, '\n');
	free(tmp_s1);
	return (0);
}

//Function	: Remplie la map du .cub dans un tab 2d de char
//Param 	: La struct data contenant map et le fd du .cub
//Return	: ERROR --> 1 || SUCCESS --> 0
static int	ft_fill_map(t_data *data)
{
	char	*tmp_s1;
	char	*s2;

	tmp_s1 = malloc(1);
	if (!tmp_s1)
		return (-1);
	tmp_s1[0] = '\0';
	s2 = get_next_line(data->fd);
	if (!s2)
		return (printf("Error\nEmpty map\n"), free(tmp_s1), -1);
	while (s2[0] == '\n')
	{
		free(s2);
		s2 = get_next_line(data->fd);
	}
	if (ft_loop_fill_map(data, tmp_s1, s2) != 0)
		return (-1);;
	return (0);
}

//Function	: Verifie les char de la map et recupere l'orientaion et la pos du player
//Param 	: La struct data, la ligne de la map a verifier (s), le nombre de player trouver, et le num de la ligne
//Return	: ERROR --> -1 || SUCCESS --> 0
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


//Function	: Recupere et verifie le contenue de la map
//Param 	: La struct data
//Return	: ERROR --> -1 || SUCCESS --> 0
int	ft_get_map(t_data *data)
{
	int	i;
	int	nb_player;

	i = 0;
	nb_player = 0;
	if (ft_fill_map(data) != 0)
		return (-1);
	while (data->m[i])
	{
		if (ft_is_map_char_valid(data, data->m[i], &nb_player, i) != 0)
			return (-1);
		i++;
	}
	if (nb_player != 1)
		return (printf("Error\nIncorrect number of players\n"), -1);
	if (ft_is_map_enclosed_wall(data) != 0)
		return (-1);
	if (ft_cpy_map(data) != 0)
		return (-1);
	return (0);
}
