/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/19 18:19:20 by gsaiago          ###   ########.fr       */
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
	if (ms_clean_words_and_init_flags_on_lst(word_lst))
		return (1);
	//ms_word_lst_flag_init(*word_lst);
	//ms_lst_remove_if(word_lst);
	free(line);
	return (0);
}

int	ms_clean_words_and_init_flags_on_lst(t_word **lst)
{
	t_word	*node;

	if (!lst || !*lst)
		return (1);
	node = *lst;
	while (node)
	{
		if (node->word)
		{
			//node->flag = ms_flag_word(node); a flag vem antes de retirar as aspas
			node->word = ms_expand_env(node->word);
			node->word = ms_remove_quotes(node->word, 1);
		}
		node = node->next;
	}
	ms_lst_remove_empty_word(lst);
	return (0);
}

int	ms_flag_word(t_word *node)
{
	char	*word;
	int		flag;

	if (!node)
		return (-1);
	word = node->word;
	if (!word)
		return (-1);
	if (ft_strncmp(node->word, "|", 2) == 0)
		return (MS_PIPE);
	flag = 1;
	while (*word)
	{

	}
	if (ft_strchr(node->word, '>'))
		return (MS_REDIRECT);
	return (MS_WORD);
}
