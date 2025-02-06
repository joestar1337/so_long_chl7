/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:04:11 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/17 16:55:22 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_nextline(char *s)
{
	int		i;
	char	*ret;
	int		len;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (free(s), NULL);
	len = ft_strlen(s) - i;
	ret = malloc(len + 1);
	if (!ret)
		return (free(s), NULL);
	i++;
	j = 0;
	while (s[i])
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (free(s), ret);
}

static int	check(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*ft_read(char *s, char *buffer, int fd)
{
	int	readed;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		buffer[readed] = '\0';
		s = ft_join(s, buffer);
		if (!s)
			return (free(buffer), NULL);
		if (check(s))
			break ;
	}
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(s), s = NULL);
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (free(s), NULL);
	s = ft_read(s, buffer, fd);
	free(buffer);
	buffer = s;
	buffer = ft_sub(buffer);
	s = ft_nextline(s);
	return (buffer);
}
