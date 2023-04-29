/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:18:20 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 13:22:42 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_lexxer(t_word **word_lst)
{
	if (!word_lst)
		return (1);
	if (ms_analyze_lexx(word_lst))
		return (1);
	if (ms_analyze_syntax(*word_lst))
		return (1);
	if (ms_analyze_cmd_syntax(*word_lst))
		return (1);
	return (0);
}

int	ms_analyze_lexx(t_word **lst)
{
	t_word	*node;
	int		last_flag;

	if (!lst || !*lst)
		return (1);
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
