#include "minishell.h"
int	get_dollar_word_len(char *line);

/*
char	*ms_expand_env(char *line);
{




}
*/

int	ms_get_len_after_expansion(char *line)
{
	int		final_len;
	char	*env_word;

	if (!line)
		return (1);
	final_len = 0;
	while (*line)
	{
		if (*line == '\'')
		{
			final_len += ms_find_next_quotes(line) + 2;
			line += ms_find_next_quotes(line) + 1;
		}
		else if (*line == '$')
		{
			env_word = ft_substr(line, 1, get_dollar_word_len(line));
			final_len += ft_strlen(getenv(env_word));
			printf("Env_word > |%s|\nFinal_len > %d\n", env_word, final_len); //debug
				line += get_dollar_word_len(line) + 1;
			if (env_word)
				free(env_word);
		}
		else
		{
			final_len++;
			line++;
		}
	}
	printf("final_len > |%d|\n", final_len); //debug
	return (final_len);
}

int	get_dollar_word_len(char *line)
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
