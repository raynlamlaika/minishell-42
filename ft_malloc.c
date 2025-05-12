#include "minishell.h"

// void    free_gc(t_gc_collector **gc_head)
// {
//     t_gc_collector    *tmp;
//     int i = 0;

//     while (*gc_head)
//     {
//         tmp = (*gc_head);
//         (*gc_head) = (*gc_head)->next;
//         free(tmp->ptr);
//         tmp->ptr = NULL;
//         free(tmp);
//         tmp = NULL;
//         i++;
//     }
//     printf("this is %d\n", i);
//     *gc_head = NULL;
// }

// void    *ft_malloc(size_t size, int flag)
// {
//     static t_gc_collector    *gc_head;
//     t_gc_collector            *node;
//     static int i;
//     if (flag)
//     { 
//         i++;
//         node = malloc(sizeof(t_gc_collector));
//         if (node == NULL)
//             return (free_gc(&gc_head),
//                 printf("Erorr malloc fail"), exit(1), NULL);
//         node->ptr = malloc(size);
//         if (node->ptr == NULL)
//         {
//             free(node);
//             return (free_gc(&gc_head),
//                 printf("Erorr malloc fail"), exit(1), NULL);
//         }
//         node->next = gc_head;
//         gc_head = node;
//         return (node->ptr);
//     }
//     else
//     {
//         printf("THIS SI I %d\n", i);
//         free_gc(&gc_head);

//     }
//     (void)size;
//     return (NULL);
// }



typedef struct s_malloc
{
	void *toalloc;
	struct s_malloc *next;
} t_malloc;

void ft_free(t_malloc **head)
{
	t_malloc *helper;

	while (*head)
	{
		helper = *head;
		*head = (*head)->next;
		free(helper->toalloc);
		helper->toalloc = NULL;
		free(helper);
		helper = NULL;
	}
	*head = NULL;
}

void *ft_malloc(unsigned int size, int flag)
{
	static t_malloc *head;
	t_malloc *to_save;

	if (flag)
	{
		to_save = malloc(sizeof(t_malloc));
		if (!to_save)
		{
			ft_free(&head);
			write(2, "malloc failed\n", 14);
			return NULL;
		}
		to_save->toalloc = malloc(size);
		if (!to_save->toalloc)
		{
			free(to_save);
			ft_free(&head);
			write(2, "malloc failed\n", 14);
			return NULL;
		}
		to_save->next = head;
		head = to_save;
		return (to_save->toalloc);  //  Fixed here
	}
	else
		ft_free(&head);
	return NULL;
}