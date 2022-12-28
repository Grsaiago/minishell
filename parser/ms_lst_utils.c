/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_lst_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:02:02 by gsaiago           #+#    #+#             */
/*   Updated: 2022/12/28 13:58:19 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

void	ms_lstadd_back(t_word **head, t_word *new)
{
	t_word	*node;

	if (!new || !head)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	node = *head;
	while (node->next)
		node = node->next;
	node->next = new;
	new->next = NULL;
	return ;
}

void	ms_word_lst_clear(t_word *head)
{
	t_word	*aux;

	while (head)
	{
		aux = head;
		if (aux->word)
			free(aux->word);
		head = head->next;
		free(aux);
	}
	return ;
}
