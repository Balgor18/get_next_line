/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/19 16:22:13 by fcatinau         ###   ########.fr       */
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
	int				bre;

	bre = 0;
	i = 0;
	line_tmp = NULL;
	while ((len = read(fd, buf, BUFFER_SIZE)))
	{
		while (i < len)// je boucle sur len pour voir toute les valeurs qu'il y a dans i
		{
			if (ft_ver_buf(buf[i]))// je verifie que buf[i] ne soit pas = a \n
			{
				if (!(line_tmp = ft_malloc(len)))// change la size du malloc
					return (-1);
				line_tmp = ft_strcpy(line_tmp, buf[i]);
				free(line_tmp);
			}
			else
			{
				bre = 1;
				break ;
			}
			printf("line_tmp %s\n", line_tmp);
			i++;
		}
		if (bre)
			break ;
		i = 0;
	}
	printf("Le seg fqult \n");
	printf("ft_strlen %p \n", ft_malloc(ft_strlen(line_tmp)));
	*line = ft_malloc(ft_strlen(line_tmp));
	*line = line_tmp;
	return (0);
}
