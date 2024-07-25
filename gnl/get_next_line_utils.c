/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:38:58 by rasamad           #+#    #+#             */
/*   Updated: 2024/07/22 16:27:53 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp;
	size_t	i;

	temp = (char *)s;
	i = 0;
	while (i < n)
	{
		temp[i] = '\0';
		i++;
	}
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

void	ft_memcpy_gnl(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
}

char	*ft_strdup_gnl(char *s)
{
	size_t	j;
	char	*tmp;

	j = 0;
	if (!s)
		return (NULL);
	tmp = malloc (sizeof(char) * (ft_strlen_gnl(s) + 1));
	if (!tmp)
		return (NULL);
	while (j < ft_strlen_gnl(s) && s[j])
	{
		tmp[j] = s[j];
		j++;
	}
	tmp[j] = '\0';
	return ((char *)tmp);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*s1_plus_s2;

	j = 0;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_gnl(s2));
	s1_plus_s2 = malloc((ft_strlen_gnl(s1) + \
	ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!s1_plus_s2)
		return (free(s1), NULL);
	while (s1[i])
	{
		s1_plus_s2[i] = s1[i];
		i++;
	}
	while (s2[j] && s2[j - 1] != '\n')
		s1_plus_s2[i++] = s2[j++];
	s1_plus_s2[i] = '\0';
	return (free(s1), s1_plus_s2);
}
