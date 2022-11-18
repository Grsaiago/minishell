/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:39:03 by gsaiago           #+#    #+#             */
/*   Updated: 2022/09/20 16:54:29 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*get_next_line(int fd)
{
	int			valid;
	static char	*sptr;
	char		*rptr;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		if (sptr)
			free(sptr);
		return (NULL);
	}
	if (!sptr)
		sptr = ft_strdup("");
	valid = 1;
	sptr = ft_gnl(valid, fd, sptr);
	if (!sptr)
		return (NULL);
	rptr = ft_returnptr(sptr);
	sptr = ft_staticptr(sptr);
	return (rptr);
}

char	*ft_gnl(int valid, int fd, char *sptr)
{
	char	*auxptr;

	while (valid && !ft_strchr(sptr, '\n'))
	{
		auxptr = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		valid = read(fd, auxptr, BUFFER_SIZE);
		if (valid < 0)
		{
			free(auxptr);
			free(sptr);
			return (NULL);
		}
		if (valid > 0)
			sptr = ft_strjoin_gnl(sptr, auxptr);
		else
			free(auxptr);
	}
	return (sptr);
}

char	*ft_returnptr(char *buffer)
{
	int		i;
	int		extra;
	char	*str;

	if (!buffer[0])
		return (NULL);
	extra = 1;
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		extra = 2;
	str = ft_calloc(sizeof(char), i + extra);
	i = 0;
	while (buffer[i] && (buffer[i] != '\n'))
	{
		str[i] = buffer [i];
		i++;
	}
	if (extra == 2)
		str[i] = '\n';
	return (str);
}

char	*ft_staticptr(char *buffer)
{
	int		i;
	char	*str;
	int		j;

	j = 0;
	i = 0;
	if (ft_strchr(buffer, '\n'))
	{
		while (buffer[i] != '\n')
			i++;
		i++;
		str = ft_calloc(sizeof(char), (ft_strlen(buffer) - i + 1));
		while (buffer[i + j])
		{
			str[j] = buffer[i + j];
			j++;
		}
		free(buffer);
		return (str);
	}
	else
		free(buffer);
	return (NULL);
}
