/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:14:58 by fcatinau          #+#    #+#             */
/*   Updated: 2021/07/08 16:15:45 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*join_str(char const *char1, char const *char2, int lire)
{
	size_t	line_max_len;
	char	*tmp;

	if (!char1 && !char2)
		return (0);
	((char *)char2)[lire] = '\0';
	line_max_len = ft_strlen((char *)char1) + ft_strlen((char *)char2) + 1;
	tmp = malloc(sizeof(char) * line_max_len);
	if (!tmp)
		return (0);
	ft_memmove(tmp, char1, ft_strlen((char *)char1));
	ft_memmove(tmp + ft_strlen((char *)char1), char2, ft_strlen((char *)char2));
	tmp[line_max_len - 1] = '\0';
	free((char *)char1);
	return (tmp);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[len - 1] = ((unsigned char *)src)[len - 1];
			len--;
		}
	}
	else
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dst);
}

int	ft_is_end(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
