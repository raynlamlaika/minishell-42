
#include "../minishell.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}


void    ft_export(char **args, t_env *env)
{
    int i;
    char *str;
    char *key;
    bool appand = false ;
    int j = 0;
    int len;
    int l = 0;

    len  = 0;
    i = 0;

    // Check if first argument is "export"
    if (ft_strncmp(&args[j][i], "export", ft_strlen("export")) != 0)
    {
        write(2, "EROOORRR\n", 9);
        return;
    }

    i++; // move to next arg after "export"

    while (args[i]) // go through all args after export
    {
        if (ft_strchr(args[i], '='))
        {
            j = 0;
            while (args[i][j])
            {
                while (ft_isalpha(args[i][j]) || ft_isdigit(args[i][j]) || args[i][j] == '"' || args[i][j] == '\'')
                {
                    len++;
                    j++;
                }
                str = ft_malloc(len, 1);
                while (len  > l)
                {
                    str[l] = args[i][l];
                    l++;
                }
                str[l] = '\0';
                l = 0;
                if (args[i][j] == '=')
                    j++;
                else if (args[i][j] == '+')
                {
                    j++;
                    len++;
                    if (args[i][j] == '=')
                    {
                        j++;
                        appand = true;
                        // HANDEL EXPAND
                    }
                    else
                        {write(1, "error\n", 6); break;}
                }
                else 
                {
                    write(2, "erooooor\n", 10);
                    break;
                }
                len++;
                while (!(args[i][j] == ' ') && (args[i][j] || args[i][j]== '\'' || args[i][j]== '\"'))
                {
                    j++;
                    l++;
                }
                key = ft_malloc(l, 1);
                l = 0;
                while (!(args[i][len] == ' ') && (args[i][len] || args[i][len]== '\'' || args[i][len]== '\"'))
                {
                    key[l] = args[i][len];
                    l++;
                    len++;
                }
                key[l] = '\0';
                printf("----> this is the key |%s| this is the value |%s|\n", key, str);

                t_env *new_node = ft_malloc(sizeof(t_env), 1);
                new_node->key = key;
                new_node->value = str;
                new_node->next = NULL;

                // Add to env linked list
                t_env *tmp = env;
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = new_node;
            }
        }
        else
        {
            j = 0;
            while (args[i][j])
            {
                if (ft_isalpha(args[i][j]))
                    j++;
                else 
                {
                    write(2, "error: invalid identifier\n", 27);
                    break;
                }
            }
        }
        i++;
    }
}
