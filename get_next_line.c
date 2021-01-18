/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/18 16:50:06 by fcatinau         ###   ########.fr       */
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

int		ft_strlen(char *c)
{
	int i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

int		ft_malloc(char *c, int size)
{
	if (!(malloc(sizeof(c) * size)))
		return (0);
	return (1);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;
	printf("Valeur d'entre %s || %s || %zu \n", dest, src , size);
	i = 0;
	if (size > 0)
	{
		printf("Je seg fqult ICI 2\n");
		while (src[i] && i < (size - 1))
		{
			printf("Je seg fqult ICI 3\n");
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i])
		i++;
	printf("Je seg fqult ICI 4\n");
	return (i);
}

int		get_next_line(int fd, char **line)
{
	char	buf[BUFFER_SIZE];
	char	*line_tmp;
	size_t	len;

	line_tmp = NULL;
	while ((len = read(fd, buf, BUFFER_SIZE)))
	{
		printf("Le seg fault des enfers\n");
		if (ft_ver_buf(buf))
			if (!ft_malloc(line_tmp, len))
				return (-1);
		printf("Le seg fault des enfers 2\n");
		ft_strlcpy(line_tmp, buf, len);
		printf("Le seg fault des enfers 3\n");
		free(line_tmp);
	}
	printf("line_tmp %s \n", line_tmp);
	ft_malloc(*line, ft_strlen(line_tmp));
	*line = line_tmp;
	return (0);
}
