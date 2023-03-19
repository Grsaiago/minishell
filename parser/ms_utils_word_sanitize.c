#include "minishell.h"
int	ms_get_env_name_len(char *line);
int	ms_get_len_after_expansion(char *line);
char	*ms_expand_env(char *line);
void	ms_expand_env_util(char *line, int i, int j, char *ret_line);
int		ms_validate_env_name(char *line);

char	*ms_expand_env(char *line)
{
	char	*ret_line;

	ret_line = ft_calloc(ms_get_len_after_expansion(line) + 1, sizeof(char));
	if (!ret_line)
		return (NULL);
	ms_expand_env_util(line, 0, 0, ret_line);
	free(line);
	return (ret_line);
}

void	ms_expand_env_util(char *line, int i, int j, char *ret_line)
{
	char	*env;
	char	flag;

	flag = 1;
	while (line[i])
	{
		if (line[i] == '\'')
			flag ^= 1;
		if (line[i] == '$' && flag && !ms_validate_env_name(&line[i]))
		{
			env = ft_substr(&line[i], 1, ms_get_env_name_len(&line[i]));
			ft_memcpy(&ret_line[j], getenv(env), ft_strlen(getenv(env)));
			i += ms_get_env_name_len(&line[i]) + 1;
			j += ft_strlen(getenv(env));
			free(env);
		}
		else
		{
			ret_line[j] = line[i];
			i++;
			j++;
		}
	}
	return ;
}

int	ms_get_len_after_expansion(char *line)
{
	int		final_len;
	char	*env_word;

	final_len = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			final_len += ms_find_next_quotes(line) + 2;
			line += ms_find_next_quotes(line) + 1;
		}
		else if (*line == '$' && !ms_validate_env_name(line))
		{
			env_word = ft_substr(line, 1, ms_get_env_name_len(line));
			final_len += ft_strlen(getenv(env_word));
			line += ms_get_env_name_len(line) + 1;
			free(env_word);
		}
		else
		{
			final_len++;
			line++;
		}
	}
	return (final_len);
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

/* daqui pra baixo tudo certin ok ?????? NÃO MEXE CARAIO*/
char	*ms_remove_quotes(char *line, int flag)
{
	char	*ret_word;
	int		i;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	ret_word = NULL;
	i = 0;
	if (!(ft_strchr(line, '\'') || ft_strchr(line, '\"')))
		return (line);
	ms_null_start_end_quotes(line);
	while (!line[i] && i < len)
		i++;
	while(i < len)
	{
		ret_word = ft_strjoin(ret_word, &line[i], 1);
		i += ft_strlen(&line[i]) + 1;
		while (!line[i] && i < len)
			i++;
	}
	if (flag)
		free(line);
	return (ret_word);
}

void	ms_null_start_end_quotes(char *line)
{
	int	next_quotes;

	if (!line)
		return ;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			next_quotes = ms_find_next_quotes(line);
			*line = '\0';
			line += next_quotes;
			*line = '\0';
			line++;
		}
		else
			line++;
	}
	return ;
}
