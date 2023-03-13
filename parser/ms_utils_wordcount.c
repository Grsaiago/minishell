/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_wordcount.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:10:10 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/12 22:45:14 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ms_null_start_end_quotes(char *line);
char	*ms_remove_quotes(char *line, int flag);

int	ms_find_next_quotes(char *line)
{
	char	quote;
	int		next_quote_distance;

	if (!line || !*line)
		return (0);
	quote = *line;
	line++;
	next_quote_distance = 1;
	while (*line != quote)
	{
		if (!*line)
			return (-1);
		next_quote_distance++;
		line++;
	}
	return (next_quote_distance);
}

char	*ms_remove_quotes(char *line, int flag)
{
	char	*ret_word;
	int		i;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	ret_word = NULL;
	i = 0;
	if (!ft_strchr(line, '\'') || !ft_strchr(line, '\"'))
		return (line);
	printf("Debug: A string antes do ms_null_start_end_quotes:\n %s\n", line); // debug
	ms_null_start_end_quotes(line);
	printf("Debug: A string depois do ms_null_start_end_quotes\n"); // debug
	write(1, line, len); // debug
	write (1, "\n", 1); //debug
	while (!line[i] && i < len)
		i++;
	while(i < len)
	{
		ret_word = ft_strjoin(ret_word, &line[i], 1);
		i += ft_strlen(&line[i]) + 1;
		while (!line[i] && i < len)
			i++;
	}
	if (flag)
		free(line);
	return (ret_word);
}

void	ms_null_start_end_quotes(char *line)
{
	int	next_quotes;

	if (!line)
		return ;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			next_quotes = ms_find_next_quotes(line);
			*line = '\0';
			line += next_quotes;
			*line = '\0';
			line++;
		}
		else
			line++;
	}
	return ;
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
			word_len += ms_find_next_quotes(line) + 1;
			line += ms_find_next_quotes(line) + 1;
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
