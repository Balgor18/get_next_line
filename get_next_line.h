/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:38:38 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/11 11:42:20 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>

int				get_next_line(int fd, char **line);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *dest, char *src);
static size_t	ft_bufflen(const char *s);
char			*ft_alloc(size_t size);
static char		*ft_save(char *lines, size_t *a);
int				get_next_line(int fd, char **line);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif
#endif

