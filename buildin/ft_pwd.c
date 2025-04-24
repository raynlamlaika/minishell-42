#include "../minishell.h"

void	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		printf ("%s\n", path);
	else
	perror("ft_pwd");
}
