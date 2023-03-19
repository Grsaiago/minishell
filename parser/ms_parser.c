/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/18 23:06:57 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parser(char *line, t_word **word_lst)
{
	*word_lst = NULL;
	if (ms_validate_quote_ammount(line))
	{
		printf("Syntax error: There is an unclosed quote\n");
		free(line);
		return (1);
	}
	*word_lst = ms_create_word_lst(line);
	if (!word_lst)
		return (1);
	if (ms_sanitize_words_on_lst(*word_lst))
		return (1);
	//ms_word_lst_flag_init(*word_lst);
	//ms_lst_remove_if(word_lst);
	free(line);
	return (0);
}

int	ms_sanitize_words_on_lst(t_word *node)
{
	if (!node)
		return (1);
	while (node)
	{
		node->word = ms_expand_env(node->word);
		node->word = ms_remove_quotes(node->word, 1);
		node = node->next;
	}
	return (0);
}
