/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 14:39:12 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/22 21:14:34 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!lst || !*lst)
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

void	ms_lst_remove_if(t_word **head)
{
	t_word	*node;

	if (!head || !*head || (*head)->flag == MS_PIPE)
		return ;
	node = *head;
	if (node->flag != MS_WORD)
	{
		*head = node->next;
		free(node->word);
		free(node);
		ms_lst_remove_if(head);
	}
	node = *head;
	if (!head || !*head || (*head)->flag == MS_PIPE)
		return ;
	ms_lst_remove_if(&node->next);
	return ;
}
