#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

# ifndef BUFF_SIZE
#  define BUFF_SIZE 2
# endif

typedef struct	s_gnl
{
	struct s_gnl	*next;
	char			buf[BUFF_SIZE];
}				t_gnl;

struct	s_data
{
	size_t	line_size;
	size_t	rd_size;
	size_t	list_buff_size;
	char	*ptrchr;

	int		error;
	t_gnl	*gnl;

};

struct 	s_mem
{
	char	str[BUFF_SIZE];
	size_t	size;
	int		status;
};

// int	get_next_line(int fd, char **line, int reset);
int	get_next_line(int fd, char **line);

void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *pointeur, int val, size_t size);
void	ft_lstdelall(t_gnl **lst);

#endif
