/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 10:29:57 by rchallie          #+#    #+#             */
/*   Updated: 2021/07/08 15:56:21 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int			get_next_line(int fd, char **line);
void		*ft_memmove(void *dst, const void *src, size_t len);
int			ft_is_end(char *str);
char		*join_str(char const *char1, char const *char2, int lire);
size_t		ft_strlen(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

#endif
