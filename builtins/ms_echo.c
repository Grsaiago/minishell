#include "minishell.h"

int	ms_echo(int ac, char **av)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	if (ac > 2)
	{
		if (!ft_strncmp(av[1], "-n", 3))
		{
			newline = 0;
			i++;
		}
		while (av[i])
		{
			printf("%s", av[i]);
			i++;
			if (av[i])
				printf(" ");
		}
	}
	if (newline)
		printf("\n");
	//status de saída global
	return (0);
}

/*
int	main(void)
{
	char	*mat[6] = {"echo", "-n", "oieoi", "shishd", "lkdbfkjsagk", NULL};
	int		count = 6;

	ms_echo(4, mat);
	return(0);
}
*/
