/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:53:49 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/21 14:48:19 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*join_str(char const *char1, char const *char2)
{
	size_t	line_max_len;
	char	*tmp;

	if (!char1 && !char2)
		return (0);
	line_max_len = ft_strlen((char *)char1) + ft_strlen((char *)char2) + 1;
	if (!(tmp = malloc(sizeof(char) * line_max_len)))
		return (0);
	ft_memmove(tmp, char1, ft_strlen((char *)char1));
	ft_memmove(tmp + ft_strlen((char *)char1), char2, ft_strlen((char *)char2));
	tmp[line_max_len - 1] = '\0';
	free((char *)char1);
	return (tmp);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	if (!dst && !src)
		return (NULL);
	i = 0;
	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (a > b)
		while (i < len)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
	else
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	return (dst);
}

int			ft_is_end(char *str)
{
	int i;

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
