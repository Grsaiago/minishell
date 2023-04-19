/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_analyze_lexx.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 12:47:22 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/19 15:17:00 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (last_flag == MS_REDIRECT_OUT || last_flag == MS_REDIRECT_IN
			|| last_flag == MS_HEREDOC)
		return (MS_REDIRECT_FILE);
	return (MS_WORD);
}
