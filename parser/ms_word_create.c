/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_word_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 21:49:48 by gsaiago           #+#    #+#             */
/*   Updated: 2022/12/21 22:37:03 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
int		count_meta_len(char *line);
int		count_word_len(char *word);
void	ms_word_lst_clear(t_word *head);

t_word	*ms_create_word_lst(char *line)
{
	t_word	*head;
	t_word	*node;
	char	*word;
	
	head = NULL;
	if (!line)
		return (NULL);
	while (*line && ft_isspace(*line))
		line++;
	while (*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		node = malloc(sizeof(t_word));
		if (!node)
			ms_word_lst_clear(head);
		word = ft_substr(line, 0, count_word_len(line));
		if (!word)
			ms_word_lst_clear(head);
		node->word = word;
		line += count_word_len(line);
		ms_lstadd_back(&head, node);
	}
	return (head);
}

int	count_meta_len(char *line)
{
	int meta;

	if (!line || !is_meta_character(*line))
		return (0);
	meta = is_meta_character(*line);
	if (ft_strlen(line) >= 2)
	{
		if (meta == line[1]) 
			return (2);
	}
	return (1);
}

int	count_word_len(char *word)
{
	int	len;

	if (!word || !word[0])
		return (0);
	len = 0;
	while (ft_isspace(*word))
		word++;
	if (is_meta_character(*word))
		return (count_meta_len(word));
	while (word[len])
	{
		if (word[len] == '\"' || word[len] == '\'')
			len += next_quotes(word + len) + 1;
		else if (ft_isspace(word[len]) || is_meta_character(word[len]))
			break ;
		len++;
	}
	return (len);
}
