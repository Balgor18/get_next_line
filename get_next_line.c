#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>
#include "get_next_line.h"

enum e_error
{
	E_SUCCESS = 0,
	E_MALLOC_FAIL = -1,
	E_READ_FAIL = -2,
};

const char *e_message[] =
{
	"-",
	"Malloc Has FAILED!",
	"Read Has FAILED!"
};

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

void	ft_print_buffer_chains(t_gnl *gnl)
{
	// dprintf(2, "%s--------------------------------------\n", "\033[33m");
	// dprintf(2, "\n\tBUFFER LIST:\n");
	while (gnl)
	{
		// dprintf(2, ">>[%.*s] |%p|\n", BUFF_SIZE, gnl->buf, gnl->next);
		gnl = gnl->next;
	}
	// dprintf(2, "--------------------------------------%s\n",  "\033[0m");
}

// void	ft_print_data(struct s_data *data, char *line)
// {
// 	// dprintf(2, "\n%s_______________________________________\n",  "\033[32m");
// 	// dprintf(2, "========================================\n");
// 	// dprintf(2, "\tSTRUCTURE DATA\n");
// 	// dprintf(2, "Line [%s]\n\n", line);
// 	// dprintf(2, "Read Value [%lu]\n", data->rd_size);
// 	// dprintf(2, "Line Size [%lu]\n", data->line_size);
// 	// dprintf(2, "Buffer list Size [%lu]\n", data->list_buff_size);
// 	// dprintf(2, "Pointer on newline >%p<\n", data->ptrchr);
// 	// dprintf(2 , "ERROR Value : [%s]\n", e_message[data->error * -1]);
// 	ft_print_buffer_chains(data->gnl);

// }

// void	ft_print_res(struct s_mem *rest)
// {

// 	// dprintf(2, "\tREST = (%lu) [%.*s]\n", rest->size, BUFF_SIZE, rest->str);
// 	// dprintf(2, "STATUS >%d<\n ", rest->status);
// }

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return ((void *)p);
		p++;
//		// dprintf(2,">>[%c] avec n [%lu]<<\n", *p, n);
	}
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src) // <= Que ce passe t-il if dest est vide? mais pas source. Proteger ou ne pas proteger tel est la question.
		return (NULL);
//	// dprintf(2, "++++++DEST >%d< ++++++SRC >%d< ++++++++SIZE >%lu< +++++=\n", ((char *)dest)[0],((const char *)src)[0], n);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
//	// dprintf(2, "++++++ END >%d< +++++++SRC >%C< +++++++++++=\n", ((char *)dest)[0], ((const char *)src)[0]);
	return (dest);
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

void	*ft_memset(void *pointeur, int val, size_t size)
{
	unsigned int	i;
	unsigned char	*copy;

	i = 0;
	copy = (unsigned char *)pointeur;
	while (i < size)
		copy[i++] = (unsigned char)val;
	pointeur = (void *)copy;
	return (pointeur);
}

void	ft_lstdelall(t_gnl **lst)
{
	t_gnl	*tmp;

	// dprintf(2, "LSTDELALL!\n");
	while (*lst)
	{
		// dprintf(2, "@@\n");
		tmp = (*lst)->next;
		// dprintf(2, "161 free lst = %p\n", *lst);
		free(*lst);
		(*lst) = tmp;
	}
}

int	ft_lstaddnew_front(struct s_data *data)
{
	t_gnl	*new_elem;

	// dprintf(2, "segfault 0.2.1\n");
	new_elem = malloc(sizeof(t_gnl));
	// dprintf(2, "173 malloc gnl %p\n", new_elem);
	if (!new_elem)
	{
		data->error =  E_MALLOC_FAIL;
		return (0);
	}
	*new_elem = (t_gnl){0};
	new_elem->next = data->gnl;
	data->gnl = new_elem;
	return (1);
}

//
// cas 1elem buf = \n => len_cpy neg donc cas particulier
//
void ft_cpy_buffer_list_free(t_gnl **gnl, struct s_mem *rest, char *line, size_t len_cpy)
{
	t_gnl *tmp;

	if (rest->status)
	{
		tmp = (*gnl)->next;
		// dprintf(2, "197 free gnl = %p\n", *gnl);
		free(*gnl);
		*gnl = tmp;
	}
	if (*gnl) // le premier maillon
	{
		// printf("%s\n", &line[-31]);
		ft_memcpy(line - (len_cpy % BUFF_SIZE), (*gnl)->buf, len_cpy % BUFF_SIZE);
		line -= len_cpy % BUFF_SIZE;
		tmp = (*gnl)->next;
		// dprintf(2, "197 free gnl = %p\n", *gnl);
		free(*gnl);
		*gnl = tmp;
	}
	// printf("avant boucle %p\n", *gnl);
	while (*gnl)
	{
		ft_memcpy(line - BUFF_SIZE, (*gnl)->buf, BUFF_SIZE);
		line -= BUFF_SIZE;
		// if ((*gnl)->next)
		tmp = (*gnl)->next;
		// printf("Error\n");
		// dprintf(2, "207 free gnl = %p\n", *gnl);
		// dprintf(2, "------------\ngnl->buf = %s\ngnl->next = %p\n------------\n",(*gnl)->buf, (*gnl)->next);
		free(*gnl);
		// dprintf(2, "209 free gnl = %p\n", *gnl);
		// printf("Error 2\n");
		// if (tmp)
		*gnl = tmp;
		// dprintf(2, "212 free gnl = %p\n", *gnl);
	}
}

int ft_no_newline_in_rest(struct s_data *data, struct s_mem *rest, char **line)
{
	// CHECK newline
	data->ptrchr = ft_memchr(rest->str, '\n', rest->size);
	// ft_print_data(data, *line);
	// ft_print_res(rest);

	// IF already read
	if (!data->ptrchr && rest->status)
		return (1);
	// IF \n
	else if (data->ptrchr)
	{
		// CALC LINE_SIZE
		data->line_size = data->ptrchr - rest->str;
	}
	else //EOF NO \N
	{
		// CALC LINE_SIZE
		data->line_size = rest->size;
		return (1);
	}

	//MALLOC
	*line = malloc(sizeof(char) * (data->line_size + 1));
	// dprintf(2, "244 malloc line %p\n", *line);
	// CHECK FAILURE
	if (!*line)
	{
		data->error = E_MALLOC_FAIL;
		return (-1);
	}

	// CPY LINE
	ft_memcpy(*line, rest->str, data->line_size);
	(*line)[data->line_size] = '\0';

	// NEW REST => rest_size - strlen(line_size) - '\n'
	rest->size = rest->size - data->line_size - 1;
	ft_memmove(rest->str, rest->str + data->line_size + 1, rest->size);

	return (0);

}

int	ft_no_buffer_in_read(struct s_data *data, struct s_mem *rest, int fd)
{
	int	ret;

	// dprintf(2, "segfault 0.2.2\n");
	ret = read(fd, data->gnl->buf, BUFF_SIZE);
	if (ret == -1)
	{
		data->error = E_READ_FAIL;
		return (-1);
	}
	else if(ret > 0)
	{
		data->rd_size = ret;
	}
	else if (ret == 0)// EOF
	{
		data->rd_size = 0;
		rest->status = 1;
		if (data->list_buff_size || rest->size)
			return (1);
		return (0);
	}
	return (data->rd_size);
}

int	ft_newline_in_buffer(struct s_data *data, struct s_mem *rest, char **line)
{
	// dprintf(2, "segfault 0.2.3\n");
	data->ptrchr = ft_memchr(data->gnl->buf, '\n', data->rd_size);
	// 	data->rd_size = data->rd_size - (data->ptrchr - data->gnl->buf) - 1;
	// ft_print_data(data, *line);
	// ft_print_res(rest);
	if (rest->status)
	{
		// dprintf(2, "segfault 0.2.3.0\n");
		data->line_size = data->list_buff_size + rest->size;
		*line = malloc(sizeof(char) * (data->line_size + 1));
		// CHECK FAILURE
		if (!*line)
		{
			data->error = E_MALLOC_FAIL;
			return (-1);
		}
		ft_memcpy(*line, rest->str, rest->size);
		(*line)[data->line_size] = '\0';

		// ft_cpy_buffer_list_free(&(data->gnl), *line + data->line_size, data->line_size - rest->size);
		ft_cpy_buffer_list_free(&(data->gnl), rest, *line + data->line_size, data->line_size - rest->size);
		*rest = (struct s_mem){};
		return (1);
	}
	else if (data->ptrchr)
	{
		// dprintf(2, "segfault 0.2.3.1\n");
		data->line_size = data->list_buff_size + (data->ptrchr - data->gnl->buf) + rest->size;
		*line = malloc(sizeof(char) * (data->line_size + 1));
		// dprintf(2, "321 malloc line = %p\n", *line);
		// CHECK FAILURE
		if (!*line)
		{
			data->error = E_MALLOC_FAIL;
			return (-1);
		}
		ft_memcpy(*line, rest->str, rest->size);
		(*line)[data->line_size] = '\0';

		ft_memcpy(rest->str, data->ptrchr + 1, data->rd_size - (data->ptrchr - data->gnl->buf) - 1);
		rest->size = data->rd_size - (data->ptrchr - data->gnl->buf) - 1;
		rest->str[rest->size] = '\0';
		// ft_memset(rest->str + rest->size, 0, 1);
		// printf("data->line_size = %zu\n", data->line_size);
		// printf("%zu = %zu - %zu \n", data->line_size - rest->size, data->line_size, rest->size);
		// ft_cpy_buffer_list_free(&(data->gnl), *line + data->line_size, data->line_size);
		// rd_size = 10
		// rest->size = data->ptrchr - data->gnl->buf

		ft_cpy_buffer_list_free(&(data->gnl), rest, *line + data->line_size, (data->rd_size - rest->size) - 1);
		// printf("380 line = %s\nline = %s\n",*line, *line - 4);
		// printf("-----------\nrest->size = %zu\ndata->rd->size = %zu\ndata->ptrchr = %zu\ndata->gnl->buf = %zu\ndata->ptrchr -data->gnl->buf = %zu - %zu\n-----------\n",rest->size, data->rd_size, data->ptrchr, data->gnl->buf, data->ptrchr - data->gnl->buf);
		// rest->size = data->rd_size - (data->ptrchr - data->gnl->buf) - 1;

		return (1);
	}
	else
	{
		// dprintf(2, "segfault 0.2.3.2\n");
		//MAYBE SOMETHING TO DO ?
	}
	return (0);
}

int	get_next_line(int fd, char **line )//, int reset)
{
	static struct s_mem	rest = (struct s_mem){};
	struct s_data		data;

	// INITIALIZATION
	// dprintf(2, "segfault 0\n");
	data = (struct s_data){0};
	*line = NULL;

	// RESET DE GNL
	// if (reset)
	// {
	// 	rest.size = 0;
	// 	rest.status = 0;
	// }
	// dprintf(2, "segfault 0.1\n");
	// IF REST

	if (rest.size && !ft_no_newline_in_rest(&data, &rest, line)) // SEARCH IN REST -> stop if error || no newline
	{
		return (1);
		return (data.line_size);
	}
	// READ
	else if (!rest.status)
	{
		// dprintf(2, "segfault 0.2\n");
		// dprintf(2, "##READING\n");
		// ft_print_res(&rest);
		// ft_print_data(&data, *line);

		while (!data.error // CHECK ERROR :
			&& ft_lstaddnew_front(&data) // INIT BUFFER -> stop if error
			&& ft_no_buffer_in_read(&data, &rest, fd) // READ IN BUFFER -> stop if error || no read
			&& !ft_newline_in_buffer(&data, &rest, line)) // SEARCH IN BUFFER -> stop if error || newline
			{
				data.list_buff_size += data.rd_size;
			}
		// dprintf(2, "##CHECK ERROR\n");
		// ft_print_res(&rest);
		// ft_print_data(&data, *line);
		// Check if error
		// printf("%zu\ndata->ptrchr = %s\ndata->gnl->buf = %s\n", data.rd_size, data.ptrchr, data.gnl->buf);
		// dprintf(2, "segfault 0.3\n");
		if (data.error)
		{
			ft_lstdelall(&(data.gnl));
			// dprintf(2, "404 free not found line %p\n", *line);
			free(*line);
			*line = NULL;
			// return (data.error);
			return (-1);
		}
		// NOTHING LEFT TO READ
		else if (!rest.size && !data.rd_size && !data.line_size)
		{
			// dprintf(2, "NOTHING to read\n");
			*line = NULL;
			return (0);
		}
		// dprintf(2, "segfault 0.4\n");
		//CREATE THE LINE or return ERROR
		//return (data.line_size);
		return (1);
	}
	// dprintf(2, "segfault 1\n");
	return (0);
}
