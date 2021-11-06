/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:07:57 by fcatinau          #+#    #+#             */
/*   Updated: 2021/11/06 14:35:22 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lstaddnew_front(struct s_data *data)
{
	t_gnl	*new_elem;

	new_elem = malloc(sizeof(t_gnl));
	if (!new_elem)
	{
		data->error = E_MALLOC_FAIL;
		return (0);
	}
	*new_elem = (t_gnl){0};
	new_elem->next = data->gnl;
	data->gnl = new_elem;
	return (1);
}

void	ft_cpy_buffer_list_free(t_gnl **gnl, char *line, size_t len_cpy)
{
	t_gnl	*tmp;

	if (*(*gnl)->buf == '\0' && (len_cpy % BUFF_SIZE) != 0)
	{
		tmp = (*gnl)->next;
		free(*gnl);
		*gnl = tmp;
	}
	if (*gnl)
	{
		ft_memcpy(line - (len_cpy % BUFF_SIZE), (*gnl)->buf,
			len_cpy % BUFF_SIZE);
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
		*gnl = tmp;
	}
}

int	ft_no_newline_in_rest(struct s_data *data, struct s_mem *rest, char **line)
{
	data->ptrchr = ft_memchr(rest->str, '\n', rest->size);
	if (!data->ptrchr && rest->status)
		return (1);
	else if (data->ptrchr)
		data->line_size = data->ptrchr - rest->str;
	else
	{
		data->line_size = rest->size;
		return (1);
	}
	*line = malloc(sizeof(char) * (data->line_size + 1));
	if (!*line)
	{
		data->error = E_MALLOC_FAIL;
		return (-1);
	}
	ft_memcpy(*line, rest->str, data->line_size);
	(*line)[data->line_size] = '\0';
	rest->size = rest->size - data->line_size - 1;
	ft_memmove(rest->str, rest->str + data->line_size + 1, rest->size);
	return (0);
}

int	ft_no_buffer_in_read(struct s_data *data, struct s_mem *rest, int fd)
{
	int	ret;

	ret = read(fd, data->gnl->buf, BUFF_SIZE);
	if (ret == -1)
	{
		data->error = E_READ_FAIL;
		return (-1);
	}
	else if (ret > 0)
		data->rd_size = ret;
	else if (ret == 0)
	{
		data->rd_size = 0;
		rest->status = 1;
		if (data->list_size || rest->size)
			return (1);
		return (0);
	}
	return (data->rd_size);
}

// fct too long
int	ft_newline_in_buffer(struct s_data *data, struct s_mem *rest, char **line)
{
	data->ptrchr = ft_memchr(data->gnl->buf, '\n', data->rd_size);
	if (rest->status)
	{
		data->line_size = data->list_size + rest->size;
		*line = malloc(sizeof(char) * (data->line_size + 1));
		if (!*line)
		{
			data->error = E_MALLOC_FAIL;
			return (-1);
		}
		ft_memcpy(*line, rest->str, rest->size);
		(*line)[data->line_size] = '\0';
		ft_cpy_buffer_list_free(&(data->gnl),
			*line + data->line_size, data->line_size - rest->size);
		*rest = (struct s_mem){};
		return (1);
	}
	else if (data->ptrchr)
	{
		data->line_size = data->list_size + (data->ptrchr - data->gnl->buf);
		data->line_size += rest->size;
		*line = malloc(sizeof(char) * (data->line_size + 1));
		if (!*line)
		{
			data->error = E_MALLOC_FAIL;
			return (-1);
		}
		ft_memcpy(*line, rest->str, rest->size);
		(*line)[data->line_size] = '\0';
		ft_memcpy(rest->str, data->ptrchr + 1,
			data->rd_size - (data->ptrchr - data->gnl->buf) - 1);
		rest->size = data->rd_size - (data->ptrchr - data->gnl->buf) - 1;
		rest->str[rest->size] = '\0';
		ft_cpy_buffer_list_free(&(data->gnl),
			*line + data->line_size, (data->rd_size - rest->size) - 1);
		return (1);
	}
	return (0);
}

//too may fct on file
//Fct to long
int	get_next_line(int fd, char **line, int reset)
{
	static struct s_mem	rest = (struct s_mem){};
	struct s_data		data;

	data = (struct s_data){0};
	*line = NULL;
	if (reset)
		rest = (struct s_mem){};
	if (rest.size && !ft_no_newline_in_rest(&data, &rest, line))
		return (data.line_size);
	else if (!rest.status)
	{
		while (!data.error && ft_lstaddnew_front(&data)
			&& ft_no_buffer_in_read(&data, &rest, fd)
			&& !ft_newline_in_buffer(&data, &rest, line))
			data.list_size += data.rd_size;
		if (data.error)
		{
			ft_lstdelall(&(data.gnl));
			free(*line);
			*line = NULL;
			return (-1);
		}
		else if (!rest.size && !data.rd_size && !data.line_size)
		{
			*line = NULL;
			return (0);
		}
		return (1);
	}
	return (0);
}
