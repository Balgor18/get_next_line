/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/18 15:48:25 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_ver_buf(char *buf)
{
	size_t i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_malloc(char *c, int size)
{
	if (!(malloc(sizeof(c) * size)))
		return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

int		get_next_line(int fd, char **line)
{
	char	buf[BUFFER_SIZE];
	char	*line_tmp;

	while (read(fd, buf, BUFFER_SIZE))
	{
		if (ft_ver_buf)
			ft_malloc(line_tmp, BUFFER_SIZE);
		ft_strlcpy(line_tmp, buf, BUFFER_SIZE);
		free(line_tmp);
	}
}
