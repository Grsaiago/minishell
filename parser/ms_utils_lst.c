/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:50:10 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/19 16:52:58 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_word	*ms_lstnew(void *word)
{
	t_word	*new;

	new = (t_word *)malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->word = word;
	new->flag = 0;
	new->pid = 0;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	return (new);
}

void	ms_lstadd_back(t_word **lst, t_word *new)
{
	t_word	*last_node;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last_node = *lst;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new;
	}
	return ;
}

void	ms_lst_remove_if(t_word **head)
{
	t_word	*node;

	if (!head || !*head)
		return ;
	node = *head;
	if (node->flag)
	{
		*head = node->next;
		free(node->word);
		free(node);
		ms_lst_remove_if(head);
	}
	node = *head;
	if (!head || !*head)
		return ;
	ms_lst_remove_if(&node->next);
	return ;
}

void	ms_lst_remove_empty_word(t_word **head)
{
	t_word	*node;

	if (!head || !*head)
		return ;
	node = *head;
	if (!node->word || !node->word[0])
	{
		*head = node->next;
		if (node->word)
			free(node->word);
		free(node);
		ms_lst_remove_if(head);
	}
	node = *head;
	if (!head || !*head)
		return ;
	ms_lst_remove_empty_word(&node->next);
	return ;
}

void	ms_lstclear(t_word **lst)
{
	void	*aux;
	t_word	*node;

	if (!lst)
		return ;
	node = *lst;
	while (node)
	{
		aux = node->next;
		free(node->word);
		free(node);
		node = aux;
	}
	*lst = NULL;
	return ;
}

/*
void	ms_word_lst_flag_init(t_word *word)
{
	while (word)
	{
		if (ms_word_assign_flag(word->word))
			word->flag = 1;
	//	word->word = ms_unquote_words(word->word); // JUST FOR TESTING
		word = word->next;
	}
	return ;
}
*/
