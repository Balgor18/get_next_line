
#include "get_next_line.h"
#include <stdio.h>

int		main(void)
{
	int		fd;
	char	**line;

	line = NULL;
	if ((fd = open("MYFILE", O_RDONLY)) < 0)
		return (-1);
	get_next_line(fd, line);
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
