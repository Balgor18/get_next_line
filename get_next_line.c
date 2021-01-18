/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/18 19:26:01 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_ver_buf(char buf)
{
	return ((buf != '\n') ? 1 : 0);
/*
** 	size_t i;
** 
** 	i = 0;
** 	while (buf[i])
** 	{
** 		if (buf[i] == '\n')
** 			return (0);
** 		i++;
** 	}
** 	return (1);
*/
}

int		ft_strlen(char *c)
{
	int i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_malloc( int size)
{
	char	*c;

	if (!(c = malloc(sizeof(char *) * size)))
		return (NULL);
	return (c);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	//printf("Valeur d'entre %s || %s || %zu \n", dest, src , size);
	i = 0;
	j = 0;
	while (dest[j])
		j++;
	if (size > 0)
	{
		while (src[i] && i < (size - 1))
		{
			//printf("Valeur d'entre %c %d || %c %d\n", dest[i], dest[i], src[i], src[i]);
			dest[j] = src[i];
			i++;
			j++;
		}
		dest[i] = '\0';
	}
	printf("dest = %s\n",dest);
	while (src[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char src)
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

int		get_next_line(int fd, char **line)
{
	char	buf[BUFFER_SIZE];
	char	*line_tmp;
	size_t	len;
	unsigned int i;

	i = 0;
	line_tmp = NULL;
	while ((len = read(fd, buf, BUFFER_SIZE)))
	{
		while (ft_ver_buf(buf[i]) && buf[i])
		{
			printf("buf %c\n", buf[i]);
			if (!(line_tmp = ft_malloc(len)))
				return (-1);
			//printf("line_temp = %s \n",line_tmp);
			line_tmp = ft_strcpy(line_tmp, buf[i]);
			//printf("line_temp = %s \n",line_tmp);
			free(line_tmp);
			i++;
		}
		if (ft_ver_buf(buf[i]))
			break;
		i = 0;
		printf("line_tpm = %s\n",line_tmp);
	}
	//printf("line_tmp %s \n", line_tmp);
	*line = ft_malloc(ft_strlen(line_tmp));
	*line = line_tmp;
	return (0);
}
