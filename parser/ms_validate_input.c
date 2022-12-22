/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:25 by gsaiago           #+#    #+#             */
/*   Updated: 2022/12/21 22:09:50 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(char *line);
int	count_word_len(char *word);
int	next_quotes(char *line);
int	is_meta_character(char c);
int	count_meta_len(char *line);
char	**ms_split_input(char *line);

int	count_words(char *line)
{
	int		words;

	words = 0;
	while (*line && ft_isspace(*line))
		line++;
	while (*line)
	{
		words++;
		while (*line && ft_isspace(*line))
			line++;
		while (*line && !ft_isspace(*line)) 
		{
			if (*line == '\'' || *line == '\"')
				line += next_quotes(line) + 1;
			else if (is_meta_character(*line))
			{
				line += count_meta_len(line);
				break ;
			}
			line++;
		}
	}
	return (words);
}
/*
int	count_word_len(char *word)
{
	int	len;

	if (!word || !word[0])
		return (0);
	len = 0;
	while (ft_isspace(*word))
		word++;
	if (is_meta_character(*word))
		return (count_meta_len(word));
	while (word[len])
	{
		if (word[len] == '\"' || word[len] == '\'')
			len += next_quotes(word + len) + 1;
		else if (!ft_isspace(word[len]) && !is_meta_character(word[len]))
			len++;
		else
			break ;
	}
	return (len);
}

int	count_meta_len(char *line)
{
	int meta;

	if (!line || !is_meta_character(*line))
		return (0);
	meta = is_meta_character(*line);
	if (ft_strlen(line) >= 2)
	{
		if (meta == line[1]) 
			return (2);
	}
	return (1);
}
*/
int	next_quotes(char *line)
{
	if (!line)
		return (0);
	if (*line == '\"')
		return (ft_strchrn(line + 1, '\"'));
	else if (*line == '\'')
		return (ft_strchrn(line + 1, '\''));
	else
		return (0);
}

int	is_meta_character(char c)
{
	if (c == '&')
		return ('&');
	else if (c == '|')
		return ('|');
	else if (c == '>')
		return ('>');
	else if (c == '<')
		return ('<');
	else
		return (0);
}

char	**ms_split_input(char *line)
{
	int		i;
	int		word_len;
	int		word_count;
	char	**mat;

	i = 0;
	word_len = 0;
	if (!line)
		return (NULL);
	word_count = count_words(line);
	mat = ft_calloc(sizeof(char *), (word_count + 1));
	if (!mat)
		return (NULL);
	while (i < word_count)
	{
		while (ft_isspace(*line))
			line++;
		word_len = count_word_len(line);
		mat[i] = ft_substr(line, 0, word_len);
		if (!mat[i])
		{
			ft_free_mat(mat);
			return (NULL);
		}
		line += word_len;
		i++;
	}
	return (mat);
}

/*
int	env_len(char *line, int start, int end)
{
	int 	env_len;
	char	*env_var;
	char	*env;

	while (*line && && (*l)


}
*/

/*
char	**ms_split_phrases(char *line, int flag)
{
	int		i;
	int		line_index;
	int		len;
	int		n_phrases;
	char	**phrase_array;

	if (!line)
		return (NULL);
	i = -1;
	line_index = 0;
	n_phrases = count_phrases(line);
	phrase_array = (char **)malloc((n_phrases + 1) * sizeof(char *));
	if (!phrase_array)
		return (NULL);
	while (++i < n_phrases)
	{
		while (ft_isspace(line[line_index]))
			line_index++;
		len = count_phrase_len(line + line_index);
		phrase_array[i] = ft_substr(line, line_index, len);
		if (!phrase_array[i])
		{
			ft_free_mat(phrase_array);
			return (NULL);
		}
		line_index += len;
	}
	phrase_array[i] = NULL;
	if (flag)
		free (line);
	return (phrase_array);
}

int	count_phrases(char *line)
{
	int i;
	int	phrases;

	i = 0;
	phrases = 1;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = next_quotes(line + i);
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			phrases++;
			if ((line[i] == '>' && line[i + 1] == '>')
				|| (line[i] == '<' && line[i + 1] == '<'))
				i++;
			phrases++;
		}
		i++;
	}
	return (phrases);
}

int	count_phrase_len(char *line)
{
	int		i;
	int		len;
	char	meta;

	i = 0;
	if (!line)
		return (0);
	len = ft_strlen(line);
	meta = is_meta_character(line[0]);
	if (len > 2 && meta == '>' && line[1] == '>')
		return (2);
	else if (len > 2 && meta == '<' && line[1] == '<')
		return (2);
	else if (meta)
		return (1);
	while (line[i] && !is_meta_character(line[i]))
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = next_quotes(line + i);
		i++;
	}
	return (i);
}
*/
