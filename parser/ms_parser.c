/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/07 19:35:50 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_redirect_out(t_word *node);
int	ms_do_redirections(t_word **word_lst);
int	ms_analyse_syntax(t_word *word_lst);
int	ms_analyze_pipe_syntax(t_word *word_lst);
int	ms_analyze_redirect_syntax(t_word *word_lst);

int	ms_parser(char *line, t_word **word_lst, t_list *env)
{
	*word_lst = NULL;
	if (ms_validate_quote_ammount(line))
	{
		printf("Syntax error: There is an unclosed quote\n");
		free(line);
		return (-1);
	}
	*word_lst = ms_create_word_lst(line, env);
	if (!word_lst)
		return (-1);
	if (ms_clean_words_and_init_flags_on_lst(word_lst))
		return (-1);
	if (ms_analyse_syntax(*word_lst))
		return (-1);
	if (ms_do_redirections(word_lst))
		return (-1);
	free(line);
	return (0);
}

int	ms_clean_words_and_init_flags_on_lst(t_word **lst)
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

int	ms_flag_word(char *word, int last_flag)
{
	if (!word)
		return (-1);
	if (ft_strncmp(word, "|", 2) == 0)
		return (MS_PIPE);
	else if (ft_strncmp(word, "<<", 3) == 0)
		return (MS_HEREDOC);
	else if (ft_strncmp(word, ">>", 3) == 0)
		return (MS_APPEND);
	else if (ft_strncmp(word, "<", 2) == 0)
		return (MS_REDIRECT_IN);
	else if (ft_strncmp(word, ">", 2) == 0)
		return (MS_REDIRECT_OUT);
	else if (last_flag == MS_REDIRECT_OUT || last_flag == MS_REDIRECT_IN)
		return (MS_REDIRECT_FILE);
	return (MS_WORD);
}

int	ms_analyse_syntax(t_word *word_lst)
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
