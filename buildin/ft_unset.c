
#include "../minishell.h"

// void remove_node(t_env **head, const char *key_to_remove)
// {
// 	t_env *current = *head;
// 	t_env *prev = NULL;

// 	while (current)
// 	{
// 		if (ft_strcmp(current->key, key_to_remove) == 0)
// 		{
// 			printf("%s ht \n", key_to_remove);

// 			if (prev)
// 				prev->next = current->next;
// 			else
// 				*head = current->next;
// 			return;
// 		}
// 		prev = current;
// 		current = current->next;
// 		if (!current)
// 			break;
// 	}
//}


void remove_node(t_env **head, const char *key_to_remove)
{
	t_env *current = *head;
	t_env *prev = NULL;

	while (current)
	{
		// printf("Comparing '%s' with '%s'\n", current->key, key_to_remove);
		if (ft_strcmp(current->key, key_to_remove) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;

			// free(current->key);
			// free(current->value);
			// free(current);
			printf("Removed: %s\n", key_to_remove);
			return;
		}
		prev = current;
		current = current->next;
	}
	// printf("Key '%s' not found\n", key_to_remove);
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
	// print_env_list(*env_list);
}
