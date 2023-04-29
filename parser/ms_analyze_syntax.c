/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:18:20 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 09:26:34 by kefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int	ms_analyze_cmd_syntax(t_word *word_lst);
int	ms_count_cmd_in_sentence(t_word *node);

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

int	ms_analyze_pipe_syntax(t_word *word_lst)
{
	t_word	*node;
	int		last_flag;

	if (!word_lst)
		return (-1);
	node = word_lst;
	last_flag = MS_PIPE;
	while (node)
	{
		if ((last_flag == MS_PIPE && node->flag == MS_PIPE)
			|| (!node->next && node->flag == MS_PIPE))
		{
			printf("Syntax error: Incorrect use of pipes\n");
			return (-1);
		}
		last_flag = node->flag;
		node = node->next;
	}
	return (0);
}

int	ms_analyze_cmd_syntax(t_word *word_lst)
{
	while (word_lst)
	{
		if (ms_count_cmd_in_sentence(word_lst) == 0)
		{
			ft_putstr_fd("Syntax error: sentence w/no command\n", STDERR_FILENO);
			return (1);
		}
		while (word_lst && word_lst->flag != MS_PIPE)
			word_lst = word_lst->next;
	}
	return (0);
}

int	ms_count_cmd_in_sentence(t_word *node)
{
	int	cmd_count;

	cmd_count = 0;
	while(node && node->flag != MS_PIPE)
	{
		if (node->flag == MS_WORD)
			cmd_count++;
		node = node->next;
	}
	return (cmd_count);
}

int	ms_analyze_redirect_syntax(t_word *word_lst)
{
	t_word	*node;

	if (!word_lst)
		return (-1);
	node = word_lst;
	while (node)
	{
		if (node->flag == MS_REDIRECT_IN || node->flag == MS_REDIRECT_OUT
			|| node->flag == MS_HEREDOC || node->flag == MS_APPEND)
		{
			if (!node->next || node->next->flag != MS_REDIRECT_FILE)
			{
				printf("Syntax error: error on '%s'\n", node->word);
				return (-1);
			}
		}
		node = node->next;
	}
	return (0);
}
