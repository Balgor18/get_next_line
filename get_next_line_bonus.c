/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:53:45 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/22 21:04:58 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char		*ft_get_save_line(char *save)
{
	char		*cpy;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (!save)
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	if (!(cpy = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1))))
		return (0);
	i++;
	while (save[i])
		cpy[j++] = save[i++];
	cpy[j] = '\0';
	free(save);
	return (cpy);
}

char		*get_line(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (!(cpy = malloc(sizeof(char) * (i + 1))))
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		cpy[i] = str[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int			get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		*save[1024];
	int				lire;

	lire = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_is_end(save[fd]) && lire != 0)
	{
		if ((lire = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[lire] = '\0';
		save[fd] = join_str(save[fd], buffer);
	}
	free(buffer);
	*line = get_line(save[fd]);
	save[fd] = ft_get_save_line(save[fd]);
	if (lire == 0)
		return (0);
	return (1);
}
