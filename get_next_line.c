/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:57:46 by fcatinau          #+#    #+#             */
/*   Updated: 2021/07/08 16:14:14 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_save_line(char *save)
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
	cpy = malloc(sizeof(char) * ((ft_strlen(save) - i) + 1));
	if (!cpy)
		return (0);
	i++;
	while (save[i])
		cpy[j++] = save[i++];
	cpy[j] = '\0';
	free(save);
	return (cpy);
}

char	*get_line(char *str)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	cpy = malloc(sizeof(char) * (i + 1));
	if (!cpy)
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

int	lire_1(char *buffer)
{
	free(buffer);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	char			*buffer;
	static char		*save;
	int				lire;

	lire = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (-1);
	while (!ft_is_end(save) && lire != 0)
	{
		lire = read(fd, buffer, BUFFER_SIZE);
		if (lire == -1)
			return (lire_1(buffer));
		save = join_str(save, buffer, lire);
	}
	free(buffer);
	*line = get_line(save);
	save = ft_get_save_line(save);
	if (lire == 0)
		return (lire);
	return (1);
}
