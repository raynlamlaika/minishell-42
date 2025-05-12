/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:17:16 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/10 01:50:15 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef struct s_malloc
{
	void    *toalloc;
	struct s_malloc *next;
}       t_malloc;


void ft_free(t_malloc **head)
{
	t_malloc  *helper;

	while (*head)
    {
        helper = (*head);
        (*head) = (*head)->next;
        free(helper->toalloc);
        helper->toalloc = NULL;
        free(helper);
        helper = NULL;
    }
	*head = NULL;
}

void	*ft_malloc(unsigned int size, int flag)
{
	static t_malloc	*head;
	t_malloc		*to_save;

	if (flag)
	{
		to_save = malloc(sizeof(t_malloc));
		if (to_save == NULL)
		{
			ft_free(&head);
			return(write(2,"malloc failed\n", 14), NULL);
		}
		to_save->toalloc = malloc(size);
		if (to_save->toalloc == NULL)
		{
			free(to_save);
			ft_free(&head);
			return(write(2,"malloc failed\n", 14), NULL);
		}
		to_save->next = head;
		head = to_save;
		return (to_save);
	}
	else
		ft_free(&head);
	return (NULL);
}



int main()
{
	while (1)
		ft_malloc(100000000, 1);

	printf("helloe\n");
	ft_malloc(0, 0);

}