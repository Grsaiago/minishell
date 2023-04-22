/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/22 20:53:36 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_parser(char *line, t_word **word_lst, t_list *env)
{
	int	err;

	err = 0;
	*word_lst = NULL;
	if (ms_validate_quote_ammount(line))
	{
		printf("Syntax error: There is an unclosed quote\n");
		free(line);
		return (-1);
	}
	*word_lst = ms_create_word_lst(line, env);
	err = ms_lexxer(*word_lst);
	add_history(line);
	free(line);
	return (err);
}

int	ms_analyze_lexx(t_word **lst)
{
	t_word	*node;
	int		last_flag;

	if (!lst || !*lst)
		return (-1);
	node = *lst;
	last_flag = 0;
	while (node)
	{
		if (node->word)
		{
			node->flag = ms_flag_word(node->word, last_flag);
			node->word = ms_expand_env(node->word, node->env_lst);
			node->word = ms_remove_quotes(node->word, 1);
			last_flag = node->flag;
		}
		node = node->next;
	}
	ms_lst_remove_empty_word(lst);
	return (0);
}

int	ms_analyze_syntax(t_word *word_lst)
{
	if (!word_lst)
		return (-1);
	else if (ms_analyze_pipe_syntax(word_lst))
		return (-1);
	else if (ms_analyze_redirect_syntax(word_lst))
		return (-1);
	return (0);
}
