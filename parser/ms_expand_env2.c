/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_env2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:57:14 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 09:29:51 by kefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_get_expanded_env_len(char *line, t_list *env)
{
	char				*env_word;
	int					len;
	extern unsigned int	g_exit_status;

	if (line && line[1] == '?')
	{
		if (g_exit_status == 0)
			return (1);
		else
			return (ms_count_decimal(g_exit_status));
	}
	env_word = ft_substr(line, 1, ms_get_env_name_len(line));
	len = ft_strlen(ms_getenv_lst(env, env_word));
	if (env_word)
		free(env_word);
	return (len);
}

int	ms_validate_env_name(char *line)
{
	if (line && line[1] == '?')
		return (0);
	if (!line || *line != '$' || !ft_isalnum(line[1]))
		return (1);
	return (0);
}

int	ms_get_env_name_len(char *line)
{
	int	word_len;

	if (!line)
		return (0);
	word_len = 0;
	line++;
	if (*line == '?')
		return (1);
	while (line && *line && ft_isalpha(*line))
	{
		word_len++;
		line++;
	}
	return (word_len);
}

int	ms_count_decimal(int n)
{
	int	len;

	len = 0;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}
