#include "minishell.h"
void	ms_cd(int ac, char **av);

int	main(void)
{
	char	*line;
	char	**mat;
	t_word	*word_lst;

	word_lst = NULL;
	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			return (0);
		}
		if (ms_parser(line, &word_lst))
			ft_putstr_fd("Error on parser\n", 3);
		mat = ms_create_mat_from_lst(word_lst);
		if (!ft_strncmp(word_lst->word, "cd", 3))
			ms_cd(ft_mat_size(mat), mat);
		else
			ms_bin_exec(word_lst);
		ms_lstclear(&word_lst);
		ft_free_mat(mat);
	}
	return (0);
}
