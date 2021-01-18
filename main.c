/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:54:22 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/18 15:49:12 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int		main(void)
{
	int		fd;
	char	**line;

	line = NULL;
	if ((fd = open("MYFILE", O_RDONLY)) < 0)
		return (-1);
	if (get_next_line(fd, line) == -1)
	{
		printf("Crash !!!!!!!!!!!!");
		return (0);
	}
	printf("1 : %s\n", *line);
	free(*line);
	get_next_line(fd, line);
	printf("2 : %s\n", *line);
	free(*line);
	get_next_line(fd, line);
	printf("3 : %s\n", *line);
	free(*line);
	get_next_line(fd, line);
	printf("4 : %s\n", *line);
	free(*line);
	get_next_line(fd, line);
	printf("5 : %s\n", *line);
	free(*line);
	close(fd);
	return (0);
}
