/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 21:14:58 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/20 13:27:27 by fcatinau         ###   ########.fr       */
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
