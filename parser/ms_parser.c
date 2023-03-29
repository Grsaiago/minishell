/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/29 15:07:10 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_redirect_out(t_word *node);
int	ms_do_redirections(t_word **word_lst);

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
	if (ms_do_redirections(word_lst))
		return (-1);
	free(line);
	return (0);
}

int	ms_clean_words_and_init_flags_on_lst(t_word **lst)
{
	t_word	*node;

	if (!lst || !*lst)
		return (-1);
	node = *lst;
	while (node)
	{
		if (node->word)
		{
			node->flag = ms_flag_word(node);
			node->word = ms_expand_env(node->word, node->env_lst);
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

	if (!node)
		return (-1);
	word = node->word;
	if (!word)
		return (-1);
	if (ft_strncmp(node->word, "|", 2) == 0)
		return (MS_PIPE);
	else if (ft_strncmp(node->word, "<<", 3) == 0)
		return (MS_HEREDOC);
	else if (ft_strncmp(node->word, ">>", 3) == 0)
		return (MS_APPEND);
	else if (ft_strncmp(node->word, "<", 2) == 0)
		return (MS_REDIRECT_IN);
	else if (ft_strncmp(node->word, ">", 2) == 0)
		return (MS_REDIRECT_OUT);
	return (MS_WORD);
}
