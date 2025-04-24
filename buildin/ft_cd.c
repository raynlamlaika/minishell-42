#include "../minishell.h"

int ft_cd(char *path)
{
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

int main(int argc , char **argv)
{
    ft_cd(argv[1]);
    ft_pwd();
    return 0;
}