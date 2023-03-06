/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_create_word_lst.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:38:40 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/28 14:22:42 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*ms_create_word_lst(char *line)
{
	int		word_len;
	t_word	*new_word;
	t_word	*word_lst;


	word_lst = NULL;
	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		word_len = get_word_len(line);
		new_word = ms_lstnew(ft_substr(line, 0, word_len));
		ms_lstadd_back(&word_lst, new_word);
		line += word_len;
		while (ft_isspace(*line))
			line++;
	}
	return (word_lst);
}

int	ms_word_assign_flag(char *word)
{
	while (*word)
	{
		if (*word == '>' || *word == '<')
			return(1);
		word++;
	}
	return (0);
}

/*
int	ms_count_words(char *line)
{
	unsigned int	words;

	while (*line && ft_isspace(*line))
		line++;
	words = 0;
	while (*line)
	{
		words++;
		while (ft_isspace(*line))
			line++;
		if (ms_ismeta(line))
			line += ms_ismeta(line);
		else if (*line && !ft_isspace(*line))
		{
			while (*line && !ft_isspace(*line) && !ms_ismeta(line))
				line++;
		}
		while (ft_isspace(*line))
			line++;
	}
	return (words);
}
*/
