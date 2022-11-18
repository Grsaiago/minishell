/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 18:22:51 by gsaiago           #+#    #+#             */
/*   Updated: 2022/06/18 14:57:39 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_valid(const char *str, char c);
static int		ft_lenc(char *s, char c);
static char		**ft_mat(char *str, char c, char **mat, int words);

char	**ft_split(char const *s, char c)
{
	char	**mat;
	char	*str;
	int		words;

	if (!s)
		return (NULL);
	str = (char *)s;
	words = ft_valid(str, c);
	mat = ft_calloc((words + 1), sizeof(char *));
	if (!mat)
		return (NULL);
	mat = ft_mat(str, c, mat, words);
	if (!mat)
		return (NULL);
	return (mat);
}

static size_t	ft_valid(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		if ((*str != c) && ((*(str + 1) == c) || (*(str + 1) == 0)))
			i++;
		str++;
	}
	return (i);
}

static int	ft_lenc(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != c))
		i++;
	return (i);
}

static char	**ft_mat(char *str, char c, char **mat, int words)
{
	int	i;

	i = -1;
	while ((++i < words) && *str)
	{
		while (*str == c && *str)
			str++;
		mat[i] = ft_substr(str, 0, ft_lenc(str, c));
		if (!mat[i])
		{
			while (mat[i])
			{
				free(mat[i]);
				i--;
			}
			return (NULL);
		}	
	str += ft_lenc(str, c);
	}
	return (mat);
}
