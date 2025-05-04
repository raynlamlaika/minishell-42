#include "../minishell.h"

char	*global_var(char set_it, char *pwd_var)
{
	static char	*pwd___;

	if (set_it)
		pwd___ = pwd_var;
	return (pwd___);
}

int ft_cd(char **args)
{
	const char	*path_____;
    char		cwd[PATH_MAX];
	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		path_____ = getenv("HOME");
		if (!path_____)
		{
			perror("cd: HOME not set");
			return (1);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		path_____ = getenv("OLDPWD");
		if (!path_____)
		{
			perror("cd: OLDPWD not set");
			return (1);
		}
		printf ("%s\n", path_____);
	}
	else
		path_____ = args[1];

	if (chdir(path_____) != 0)
	{
		perror("cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
	}
	return (0);
}
