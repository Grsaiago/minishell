/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:25 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/24 22:14:40 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
		if (line[i] == '"' || line[i] == ''')
			i = next_quotes(line[i]);
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
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

}

int	count_word_len(char *phrase)
{
	int	i;
	int	len;
	int	env_len;

	if (!line || !line[0])
		return (0);
	i = 0;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	while (line[i + len])
	{
		if (line[i + len] == '"' || line[i + len] == ''')
			len = next_quotes(line[i]) + 1;
		else if (!ft_isspace(line[i + len]))
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

int	next_quotes(char *line)
{
	if (!line)
		return (0);
	if (*line == ''')
		return (ft_strchrn(line + 1, '"'));
	else if (*line == ''')
		return (ft_strchrn(line + 1, '''));
	else
		return (0);
}
*/

int	count_words(char *line)
{
	int		words;

	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		if (*line == ''' || *line == '"')
			line += next_quotes(line);
		line++;
		words++;
	}
	return (words);
}

int	is_meta_character(char c)
{
	if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		return (1);
	else
		return (0);
}

/* SPLIT DA PIPEX DO GUEDES */

static int	calc_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == 34)
		{
			i++;
			while (s[i] != 34 && s[i])
				i++;
		}
		if (s[i] == 39)
		{
			i++;
			while (s[i] != 39 && s[i])
				i++;
		}
		i++;
	}
	return (i);
}

static int	start(char const *s, char c)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	return (i);
}

char	**ms_split_phrases(char const *s, char c)
{
	int		i;
	int		len;
	int		n_phrases;
	char	**array;

	if (!s)
		return (NULL);
	i = 0;
	n_phrases = count_phrases(s); 
	array = (char **)malloc((n_phrases+ 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (i < n_phrases)
	{
		while (ft_isspace(*s))
			s++;
		len = calc_len(s, c);
		array[i] = ft_substr(s, 0, len);
		array[i] = ft_remove_quotes(array[i]);
		s += len;
		i++;
	}
	array[i] = NULL;
	return (array);
}
