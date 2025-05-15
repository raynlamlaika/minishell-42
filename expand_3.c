/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlamlaik <rlamlaik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 01:01:05 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:04 by rlamlaik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int split_allocation(char *result)
{
    int size = 0;
    int i = 0;
    int n = 0;
    int m = 0;
    int y = 0;
    
    while (result[i])
    {
        if (result[i] == '\"' && m % 2 == 0)
        {
            n++;
            y = n;
        }
        if (result[i] == '\'' && n % 2 == 0)
        {
            m++;
            y = m;
        }
        size++;
        i++;
        if (y % 2 == 0 && result[i] == ' ')
        {
            while (result[i] == ' ')
                i++;
            break;
        }
    }
    return (size);
}

char *s_split(char *result, t_token *token)
{
    char *str;
    int i = 0;
    int n = 0;
    int m = 0;
    int y = 0;
    int a= 0;
    int size = split_allocation(result);
    int add = 0;
    str = ft_malloc(size + 1, 1);

    while (result[i])
    {
        a = 0;
        while(result[i])
        {
            if(result[i] == '\"' && m % 2 == 0)
            {
                n++;
                y = n;
            }
            if(result[i] == '\'' && n % 2 == 0)
            {
                m++;
                y = m;
            }
            if (y % 2 != 0)
            {
                str[a++] = result[i++];
            }
            else
            {
                str[a++] = result[i++];
                if(result[i] == ' ')
                {
                    while(result[i] == ' ')
                        i++;
                    break ;
                }
            }
        }
        str[a] = '\0';
        if (add == 0)
        {
            token->value = ft_handel_qoute(str);
            add = 1;
        }
        else
        {
            t_token *new_node = create_token(str);
            insert_token_after(token, new_node);
            token = new_node; // Move to the new node
        }
        
        if (result[i]) // Only allocate if more tokens coming
        {
            size = split_allocation(result + i);
            str = ft_malloc(size + 1, 1);
        }
    }
    return result;
}


