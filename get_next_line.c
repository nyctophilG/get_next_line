/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gosahin <gosahin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 14:51:48 by gosahin           #+#    #+#             */
/*   Updated: 2024/12/20 13:05:33 by gosahin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(int fd, char *txt, int readed)
{
	char	*buf;

	if (txt == NULL)
	{
		txt = malloc(1 * sizeof(char));
		txt[0] = '\0';
	}
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while ((ft_strchr(txt, '\n') == NULL) && readed > 0)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
		{
			free(txt);
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		txt = ft_strjoin(txt, buf);
	}
	free(buf);
	return (txt);
}

static char	*ft_extract(char *txt)
{
	char	*line;
	size_t	i;

	i = 0;
	if (txt[i] == '\0')
		return (NULL);
	while (txt[i] != '\n' && txt[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (txt[i] != '\n' && txt[i] != '\0')
	{
		line[i] = txt[i];
		i++;
	}
	if (txt[i] == '\n')
	{
		line[i] = txt[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_remember(char *txt, size_t i)
{
	char	*rem;
	size_t	j;

	j = 0;
	while (txt[i] != '\n' && txt[i] != '\0')
		i++;
	if (txt[i] == '\0')
	{
		free(txt);
		return (NULL);
	}
	rem = (char *)malloc(sizeof(char) * (ft_strlen(txt) - i));
	if (rem == NULL)
		return (NULL);
	i++;
	while (txt[i] != '\0')
	{
		rem[j] = txt[i];
		i++;
		j++;
	}
	rem[j] = '\0';
	free(txt);
	return (rem);
}

char	*get_next_line(int fd)
{
	static char	*txt;
	char		*line;
	int			readed;
	size_t		i;

	i = 0;
	readed = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	txt = ft_read(fd, txt, readed);
	if (txt == NULL)
	{
		free(txt);
		txt = NULL;
		return (NULL);
	}
	line = ft_extract(txt);
	txt = ft_remember(txt, i);
	return (line);
}
