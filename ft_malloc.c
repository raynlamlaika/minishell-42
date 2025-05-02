#include "minishell.h"

void    free_gc(t_gc_collector **gc_head)
{
    t_gc_collector    *tmp;
    int i = 0;

    while (*gc_head)
    {
        tmp = (*gc_head);
        (*gc_head) = (*gc_head)->next;
        free(tmp->ptr);
        tmp->ptr = NULL;
        free(tmp);
        tmp = NULL;
        i++;
    }
    printf("this is %d\n", i);
    *gc_head = NULL;
}

void    *ft_malloc(size_t size, int flag)
{
    static t_gc_collector    *gc_head;
    t_gc_collector            *node;
    static int i;
    if (flag)
    { 
        i++;
        node = malloc(sizeof(t_gc_collector));
        if (node == NULL)
            return (free_gc(&gc_head),
                printf("Erorr malloc fail"), exit(1), NULL);
        node->ptr = malloc(size);
        if (node->ptr == NULL)
        {
            free(node);
            return (free_gc(&gc_head),
                printf("Erorr malloc fail"), exit(1), NULL);
        }
        node->next = gc_head;
        gc_head = node;
        return (node->ptr);
    }
    else
    {
        printf("THIS SI I %d\n", i);
        free_gc(&gc_head);

    }
    (void)size;
    return (NULL);
}