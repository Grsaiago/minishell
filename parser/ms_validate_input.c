/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:25 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/28 21:39:29 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
char	***create_argv_array(t_shell s_shell)
{
	char	***argv_array;
	int		phrases;
	int		i;

	i = 0;
	if (s_shell->input_line)
		return (NULL);
	phrases = count_phrases(s_shell->input_line);
	argv_array = ft_calloc(sizeof(char *), phrases + 1);
	if (!argv_array)
		return (NULL);
	while (i < phrases)
	{
		argv_array[i] = 
		i++;
	}

}

char **create_argv(t_shell s_shell)
{
	char	**av;
	int		i;

	if (!s_shell->input_line)
		return (NULL);

}

char	**minishell_split(t_shell s_shell)
{
	int		quotes_len;
	int		i;
	char	**av;

	
}
*/

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

int	count_word_len(char *phrase)
{
	int	i;
	int	len;
	int	env_len;

	if (!phrase || !phrase[0])
		return (0);
	i = 0;
	len = 0;
	while (ft_isspace(phrase[i]))
		i++;
	while (phrase[i + len])
	{
		if (phrase[i + len] == '\"' || phrase[i + len] == '\'')
			len = next_quotes(phrase + i + 1);
		else if (!ft_isspace(phrase[i + len]))
			len++;
		else
			break ;
	}
	len += env_len;
	return (len);
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

int	next_quotes(char *line)
{
	if (!line)
		return (0);
	if (*line == '\'')
		return (ft_strchrn(line + 1, '\"'));
	else if (*line == '\'')
		return (ft_strchrn(line + 1, '\''));
	else
		return (0);
}

int	count_words(char *line)
{
	int		words;

	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			line += next_quotes(line);
		line++;
		words++;
	}
	return (words);
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
