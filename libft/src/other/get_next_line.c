/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weilin <weilin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 19:27:10 by weilin            #+#    #+#             */
/*   Updated: 2020/06/20 15:24:30 by weilin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_return_line(char **s, char **line, const int fd, int rd)
{
	char		*n;
	int			len;
	int			slen;

	if (s[fd] && s[fd][0] != '\0' && (n = ft_strchr(s[fd], '\n')))
	{
		len = n - s[fd];
		slen = ft_strlen(s[fd]);
		*line = ft_strsub(s[fd], 0, len);
		s[fd] = ft_strreset(s[fd], ft_strsub(s[fd], len + 1, slen - len - 1));
		return (s[fd] != NULL ? 1 : -1);
	}
	else if (s[fd] && s[fd][0] != '\0')
	{
		*line = ft_strdup(s[fd]);
		ft_strdel(&s[fd]);
		if (ft_strlen(*line) == 0 && rd == 0)
		{
			*line = ft_strreset(*line, "\0");
			return (0);
		}
		return (1);
	}
	s[fd] ? ft_strdel(&s[fd]) : 0;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char	*s[256];
	int			rd;
	char		*buff;

	rd = 0;
	if (fd < 0 || !line || read(fd, NULL, 0) < 0 || BUFF_SIZE < 1 ||
		!(buff = ft_strnew(BUFF_SIZE)))
		return (-1);
	while ((rd = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rd] = '\0';
		if (s[fd])
			s[fd] = ft_strreset(s[fd], ft_strjoin(s[fd], buff));
		else
			s[fd] = ft_strdup(buff);
		if (ft_strchr(buff, '\n'))
			break ;
		ft_strclr(buff);
	}
	ft_strdel(&buff);
	return (ft_return_line(s, line, fd, rd));
}
