
#include "../minishell.h"

void	ft_pwd(void)
{
	char	cwd[4096];
	char	*pwd;

	if (getcwd(cwd, sizeof(cwd)))
		printf("%s\n", cwd);
	else
	{
		pwd = getenv("PWD");
		if (pwd)
			printf("%s\n", pwd);
		else
			perror("pwd");
	}
}