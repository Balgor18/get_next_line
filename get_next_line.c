/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:16:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/14 14:34:18 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_len(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_len((char *)s1);
		len2 = ft_len((char *)s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}

char			*ft_alloc(size_t size)
{
	char	*s;
	char	*ptr;

	s = (char *)malloc(sizeof(char) * (size + 1));
	if (s == NULL)
		return (NULL);
	size = size + 1;
	ptr = s;
	while (size-- > 0)
		*ptr++ = '\0';
	return (s);
}

static char		*ft_save(char *lines, size_t *a)
{
	if (ft_strchr(lines, '\n'))
	{
		ft_strcpy(lines, ft_strchr(lines, '\n') + 1);
		return (lines);
	}
	if (ft_len(lines) > 0)
	{
		ft_strcpy(lines, ft_strchr(lines, '\0'));
		*a = 0;
		return (lines);
	}
	return (NULL);
}

int				get_next_line(int fd, char **line)
{
	char		*line_tmp;
	size_t		a;
	static char	buf[BUFFER_SIZE + 1];
	static char	*lines = NULL;
	int			end_buff;

	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	if (!(lines = ft_alloc(0)))
		return (-1);
	while (ft_strchr(lines, '\n') == NULL &&
		(end_buff = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[end_buff] = '\0';
		line_tmp = lines;
		lines = ft_strjoin(line_tmp, buf);
		free(line_tmp);
	}
	*line = ft_substr(lines, 0, ft_len(lines));
	if ((ft_save(lines, &a) != NULL) && a == 1)
		return (1);
	free(lines);
	lines = NULL;
	return (0);
}
