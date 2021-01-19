/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/19 22:59:46 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_malloc(int size)
{
	char	*c;

	if (!(c = malloc(sizeof(char *) * size)))
		return (NULL);
	return (c);
}

char		*ft_while_cpy(int len, char *tmp, char *buf, int *bre)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		if (ft_ver_buf(buf[i]))
		{
			if (!(tmp = malloc(sizeof(char *) * len)))
				return (NULL);
			tmp = ft_strcpy(tmp, buf[i]);
			free(tmp);
		}
		else
		{
			*bre = 1;
			break ;
		}
		i++;
	}
	return (tmp);
}

int			get_next_line(int fd, char **line)
{
	char			buf[BUFFER_SIZE];
	static char		*line_tmp;
	size_t			len;
	int				bre;

	bre = 0;
	line_tmp = NULL;
	while ((len = read(fd, buf, BUFFER_SIZE)))
	{
		line_tmp = ft_while_cpy(len, line_tmp, buf, &bre);
		if (bre)
			break ;
	}
	printf("line_tmp = %s \n",line_tmp);
	//*line = ft_malloc(ft_strlen(line_tmp));
	//if (!(*line = (char *)malloc(sizeof(char) * ft_strlen(line_tmp))))
	//	return (-1);
	//printf("line_tmp = %s \n",line_tmp);
	//ft_strlcpy(*line, line_tmp, ft_strlen(line_tmp));
	*line = line_tmp;
	return (0);
}
