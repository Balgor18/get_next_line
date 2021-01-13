/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatinau <fcatinau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:16:15 by fcatinau          #+#    #+#             */
/*   Updated: 2021/01/13 18:24:12 by fcatinau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**  fd(files descriptor) = 0 1 2
**  0 = stdin entree standart
**  1 = stdout sortie standart
**  2 = stderr erreur standart
*/

int		get_next_line(int fd, char **line)
{
	char		*line_tmp; // temporaire donc pas besoin de gardez ses valeurs
	size_t		a;
	static char	buf[BUFFER_SIZE + 1];
	static char	*lines = NULL;
	int			end_buff;

	/*
	** lines est la variable qui sera afficher dans le terminal
	** donc essentiel qu'elle soit static
	** -------------------------------------------------
	** Pourquoi j'aurai besoin que mon buffer soit static
	** car a chaque tours il prendre le nombre de caracteres
	** en plus et le buffer vas reasigner
	** ----------------------------------
	** verif que la buffer size est bonne
	*/
	if (fd < 0 || BUFFER_SIZE < 1 || line == NULL || read(fd, buf, 0) < 0)
		return (-1);
	/*
	** pour read() le dernier 0 correspond a read only
	**	return -1 pour erreur
	*/
	if (!(lines = ft_alloc(0)))
		return (-1);
/*
** verifie si il peut alloc sans problem
** -------------------------------------
** cas ou nous sommes en fin de ligne
*/
	while (ft_strchr(lines, '\n') == NULL &&
		(end_buff = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[end_buff] = '\0';
		line_tmp = lines;
		lines = ft_strjoin(line_tmp, buf);
		free(line_tmp);
	}
}
