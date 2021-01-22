/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 14:44:07 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/21 14:48:30 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

int			get_next_line(int fd, char **line);
void		*ft_memmove(void *dst, const void *src, size_t len);
int			ft_is_end(char *str);
char		*join_str(char const *char1, char const *char2);
size_t		ft_strlen(const char *s);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

#endif
