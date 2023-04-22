/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:08:52 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/22 17:24:38 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_expand_env(char *line, t_list *env)
{
	char	*ret_line;

	ret_line = ft_calloc(ms_get_len_after_expansion(line, env) + 1,
			sizeof(char));
	if (ret_line)
		ms_expand_env_util(line, 0, 0, ret_line, env);
	free(line);
	return (ret_line);
}

void	ms_expand_env_util(char *line, int i, int j, char *ret_line, t_list *env)
{
	char	must_expand;
	char	in_double_quotes;

	must_expand = 1;
	in_double_quotes = 1;
	while (line[i])
	{
		if (line[i] == '\"' && must_expand)
			in_double_quotes ^= 1;
		if (line[i] == '\'' && in_double_quotes)
			must_expand ^= 1;
		if (line[i] == '$' && must_expand && !ms_validate_env_name(&line[i]))
			ms_expand_env_util2(line, ret_line, &i, &j, env);
		else
		{
			ret_line[j] = line[i];
			i++;
			j++;
		}
	}
	return ;
}

void	ms_expand_env_util2(char *line, char *ret_line, int *i, int *j, t_list *env)
{
	char	*env_value;
	int		env_len;

	env_value = ft_substr(&line[*i], 1, ms_get_env_name_len(&line[*i]));
	env_len = ft_strlen(ms_getenv_lst(env, env_value));
	ft_memcpy(&ret_line[*j], ms_getenv_lst(env, env_value), env_len);
	*i += ms_get_env_name_len(&line[*i]) + 1;
	*j += env_len;
	free(env_value);
	return ;
}

int	ms_get_len_after_expansion(char *line, t_list *env)
{
	int		final_len;
	char	must_expand;
	char	in_double_quotes;

	in_double_quotes = 0;
	must_expand = 1;
	final_len = 0;
	while (*line)
	{
		if (*line == '\"' && must_expand)
			in_double_quotes ^= 1;
		if (*line == '\'' && !in_double_quotes)
			must_expand ^= 1;
		if (*line == '$' && must_expand && !ms_validate_env_name(line))
		{
			final_len += ms_get_expanded_env_len(line, env);
			line += ms_get_env_name_len(line) + 1;
		}
		else
		{
			final_len++;
			line++;
		}
	}
	return (final_len);
}
