#include "../minishell.h"

void remove_node(t_env **head, const char *key_to_remove)
{
    t_env *current;
    t_env *prev;

    prev = NULL;
    current = *head;
    if (!head || !*head)
        return;

    while (current)
    {
        if (ft_strcmp(current->key, key_to_remove) == 0)
        {
            if (prev)
                prev->next = current->next;
            else
                *head = current->next;
            current->key =  NULL;
            current->value = NULL;
            current = NULL;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void ft_unset(char **args, t_env **env_list)
{
    int i;

    i = 1;
    
    if (!*env_list)
        return;
    while (args[i])
    {
        if (ft_strncmp(args[i], "_", 2) == 0)
            i++;
        else
        {
            remove_node(env_list, args[i]);
        }
        i++;
    }
}
