/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:14:36 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/22 16:28:19 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1] = "\0";
	static int	check_read = 0;
	char		*line;
	static int	check_buff = 0;

	line = check_input_and_init_line(fd);
	if (!line)
		return (free(line), NULL);
	if (buff[0] != 0)
	{
		ft_memcpy_gnl(buff + 0, buff + ft_check_buff(buff, 2));
		line = ft_strjoin_gnl(line, buff);
		check_buff = ft_check_buff(buff, 1);
		if (buff[check_buff] == '\n')
			return (line);
	}
	check_read = read(fd, buff, BUFFER_SIZE);
	if (check_read < 0)
		return (ft_read_error(buff, line));
	buff[check_read] = 0;
	if (check_read <= 0 && check_buff == 0)
		return (free(line), NULL);
	return (print_line(line, buff, &check_buff, fd));
}

char	*check_input_and_init_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(1 * sizeof(char));
	if (line)
		line[0] = '\0';
	return (line);
}

void	*ft_read_error(char *buff, char *line)
{
	ft_bzero(buff, 1);
	return (free(line), NULL);
}

char	*print_line(char *line, char *buff, int *check_buff, int fd)
{
	int	check_read;

	*check_buff = ft_check_buff(buff, 1);
	if (*check_buff < BUFFER_SIZE)
		line = ft_strjoin_gnl(line, buff);
	else
	{
		while (*check_buff == BUFFER_SIZE)
		{
			line = ft_strjoin_gnl(line, buff);
			check_read = read(fd, buff, BUFFER_SIZE);
			if (check_read < 0)
				return (ft_read_error(buff, line));
			buff[check_read] = 0;
			*check_buff = ft_check_buff(buff, 1);
		}
		line = ft_strjoin_gnl(line, buff);
	}
	return (line);
}

int	ft_check_buff(char *buff, int choice)
{
	size_t	i;

	i = 0;
	if (choice == 1)
	{
		while (i < BUFFER_SIZE)
		{
			if (buff[i] == '\n' || buff[i] == '\0')
				return (i);
			i++;
		}
	}
	if (choice == 2)
	{
		while (i < BUFFER_SIZE)
		{
			if (buff[i] == '\n')
				return (i + 1);
			i++;
		}
	}
	return (i);
}
