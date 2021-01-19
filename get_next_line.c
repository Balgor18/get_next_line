/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/19 11:45:04 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_ver_buf(char buf)
{
	int bo;

	bo = 1;
	if (!buf || buf == '\n')
		bo = 0;
	return (bo);
}

int			ft_strlen(char *c)
{
	int i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char		*ft_malloc(int size)
{
	char	*c;

	if (!(c = malloc(sizeof(char *) * size)))
		return (NULL);
	return (c);
}

char		*ft_strcpy(char *dest, char src)
{
	int j;

	j = 0;
	while (dest[j])
		j++;
	dest[j] = src;
	j++;
	dest[j] = '\0';
	return (dest);
}

int			get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE];
	char			*line_tmp;
	size_t			len;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	line_tmp = NULL;
	while ((len = read(fd, buf, BUFFER_SIZE)))
	{
		printf("%d && %c \n", ft_ver_buf(buf[i]), buf[i]);
		while (ft_ver_buf(buf[i]) && buf[i])
		{
			printf("buf %c\n", buf[i]);
			//printf("line_tmp %s\n", line_tmp);
			if (!(line_tmp = ft_malloc(len)))
				return (-1);
			line_tmp = ft_strcpy(line_tmp, buf[i]);
			free(line_tmp);
			i++;
			j++;
		}
		printf("Avant break || %s\n", line_tmp);
		//printf("Je renvoie with - 1 %d || %c \n", ft_ver_buf(buf[i - 1]), buf[i - 1]);
		//printf("Je renvoie %d || %c || %d \n", ft_ver_buf(buf[i]), buf[i], buf[i]);
		if (!ft_ver_buf(buf[i - 1]) || j == 125)
			break ;
		i = 0;
	}
	*line = ft_malloc(ft_strlen(line_tmp));
	*line = line_tmp;
	return (0);
}
