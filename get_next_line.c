/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/20 14:22:31 by fcatinau         ###   ########.fr       */
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

char		*get_line(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
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
	printf("line_tmp = %s \n", line_tmp);
	*line = get_line(line_tmp);
	printf("Je sors de GNL\n");
	return (0);
}
