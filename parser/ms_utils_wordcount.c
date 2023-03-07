/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_wordcount.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:10:10 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/07 16:44:41 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_find_next_quotes(char *line)
{
	char	quote;
	int		next_quote_distance;

	if (!line || !*line)
		return (0);
	next_quote_distance = 0;
	quote = *line;
	line++;
	while (*line != quote)
	{
		if (!*line)
			return (-1);
		next_quote_distance++;
		line++;
	}
	return (next_quote_distance);
}

char	*ms_unquote_words(char *line)
{
	char	*ret_word;
	int		i;
	int		last_position;

	if (!line)
		return (NULL);
	ret_word = NULL;
	i = 0;
	last_position = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (last_position == 0)
				last_position++;
			ret_word = ft_strjoin(ret_word, ft_substr(&line[i], last_position, ms_find_next_quotes(&line[i])), 3);
			last_position += i + ms_find_next_quotes(&line[i]) + 1;
		}
		else
			i++;
	}
	return (ret_word);
}

int	get_word_len(char *line)
{
	int	word_len;

	if (ms_ismeta(line))
		return (ms_ismeta(line));
	word_len = 0;
	while (*line && !ms_ismeta(line) && !ft_isspace(*line))
	{
		if (*line == '\'' || *line == '\"')
		{
			word_len += ms_find_next_quotes(line) + 2;
			line += ms_find_next_quotes(line) + 2;
		}
		else
		{
			word_len++;
			line++;
		}
	}
	return (word_len);
}

int	ms_ismeta(char *c)
{
	if ((c[0] == '<' && c[1] == '<') || (c[0] == '>' && c[1] == '>'))
		return (2);
	else if (*c == '|') //*c == '>' || *c == '<')
		return (1);
	return (0);
}
