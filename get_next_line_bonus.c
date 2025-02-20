/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgosselk <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:10:42 by lgosselk          #+#    #+#             */
/*   Updated: 2023/11/06 15:10:47 by lgosselk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *remind)
{
	int		i;
	char	*str;

	i = 0;
	if (!remind[i])
		return (NULL);
	while (remind[i] && remind[i] != '\n')
		i++;
	str = (char *) malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (remind[i] && remind[i] != '\n')
	{
		str[i] = remind[i];
		i++;
	}
	if (remind[i] && remind[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

char	*ft_substr_remind(char *remind)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (remind[i] && remind[i] != '\n')
		i++;
	if (!remind[i])
	{
		free(remind);
		return (NULL);
	}
	str = (char *) malloc((ft_strlen(remind) - i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (remind[i])
		str[j++] = remind[i++];
	str[j] = '\0';
	free(remind);
	return (str);
}

char	*ft_to_remind(char	*remind, char *buff)
{
	char	*temp;

	if (remind)
	{
		temp = remind;
		remind = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
	}
	else
		remind = ft_strdup(buff);
	return (remind);
}

char	*ft_read(int fd, char *remind)
{
	int		byte;
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	byte = 1;
	while (byte != 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			free(remind);
			return (NULL);
		}
		buff[byte] = '\0';
		remind = ft_to_remind(remind, buff);
		if (ft_strchr(remind, '\n'))
			break ;
	}
	free(buff);
	return (remind);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*remind[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	remind[fd] = ft_read(fd, remind[fd]);
	if (remind[fd] == NULL)
	{
		free(remind[fd]);
		return (NULL);
	}
	line = ft_get_line(remind[fd]);
	remind[fd] = ft_substr_remind(remind[fd]);
	return (line);
}
