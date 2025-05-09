
#include "../minishell.h"

void remove_node(t_env **head, const char *key_to_remove)
{
	t_env *current = *head;
	t_env *prev = NULL;

	while (current)
	{
		if (strcmp(current->key, key_to_remove) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;

			free(current->key);
			free(current->value);
			if (current->env_v)
			{
				for (int i = 0; current->env_v[i]; i++)
					free(current->env_v[i]);
				free(current->env_v);
			}
			free(current);
			return;
		}
		prev = current;
		current = current->next;
		if (!current)
			break;
	}
}

void ft_unset(char **args, t_env **env_list)
{
	int i = 1;
	while (args[i])
	{
		if (ft_strncmp(args[i], "_", 2) == 0)
		{
			printf("manayatak asa7bi\n");
			i++;
			continue;
		}
		remove_node(env_list, args[i]);
		i++;
	}
}

