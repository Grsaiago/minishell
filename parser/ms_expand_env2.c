/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_env2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 19:57:14 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/25 12:00:44 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_get_expanded_env_len(char *line, t_list *env)
{
	char	*env_word;
	int		len;

	env_word = ft_substr(line, 1, ms_get_env_name_len(line));
	len = ft_strlen(ms_getenv_lst(env, env_word));
	if (env_word)
		free(env_word);
	return (len);
}

int	ms_validate_env_name(char *line)
{
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
	while (line && *line && ft_isalpha(*line))
	{
		word_len++;
		line++;
	}
	return (word_len);
}
