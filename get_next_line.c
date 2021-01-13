/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:16:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/13 16:16:26 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**  fd = 0 1 2
**  0 = stdin entree standart
**  1 = stdout sortie standart
**  2 = stderr erreur standart
*/

int		get_next_line(int fd, char **line)
{
	char	*line_tmp;
	size_t	a;
	char	buf[BUFFER_SIZE];

	if (fd < 0 || line == NULL)
		return (-1);
	read(line, buf, 0);
}
