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

int	ft_lstaddnew_front(struct s_data *data)
{
	t_gnl	*new_elem;

	new_elem = malloc(sizeof(t_gnl));
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


void ft_cpy_buffer_list_free(t_gnl **gnl, char *line, size_t len_cpy)
{
	t_gnl *tmp;

	if (*(*gnl)->buf == '\0' && (len_cpy % BUFF_SIZE) != 0)
	{
		tmp = (*gnl)->next;
		free(*gnl);
		*gnl = tmp;
	}
	if (*gnl) // le premier maillon
	{
		ft_memcpy(line - (len_cpy % BUFF_SIZE), (*gnl)->buf, len_cpy % BUFF_SIZE);
		line -= len_cpy % BUFF_SIZE;
		tmp = (*gnl)->next;
		free(*gnl);
		*gnl = tmp;
	}
	while (*gnl)
	{
		ft_memcpy(line - BUFF_SIZE, (*gnl)->buf, BUFF_SIZE);
		line -= BUFF_SIZE;
		tmp = (*gnl)->next;
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
	// t_gnl *tmp;

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
		// printf("gnl->buf = %.s\n", data->gnl->buf);
		// printf("gnl->next->buf = %p\n", data->gnl->next);
		// tmp = data->gnl->next;
		// free(data->gnl);
		// data->gnl = tmp;
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

		ft_cpy_buffer_list_free(&(data->gnl), *line + data->line_size, data->line_size - rest->size);
		// ft_cpy_buffer_list_free(&(data->gnl), rest, *line + data->line_size, data->line_size - rest->size);
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

		ft_cpy_buffer_list_free(&(data->gnl), *line + data->line_size, (data->rd_size - rest->size) - 1);
		// ft_cpy_buffer_list_free(&(data->gnl), rest, *line + data->line_size, (data->rd_size - rest->size) - 1);
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
