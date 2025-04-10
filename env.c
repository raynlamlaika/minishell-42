/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabba <abouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 09:24:23 by rlamlaik          #+#    #+#             */
/*   Updated: 2025/04/09 15:16:48 by abouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// char *handling_qoutes(char *word, char sepa)
// {
//     int i = 0;
//     int count = 0;
//     char *result;
//     int j = 0;
    
//     while (word[i])
//     {
//         if (word[i] != sepa)
//             count++;
//         i++;
//     }
//     result = malloc(count + 1);
//     if (!result)
//         return NULL;

//     i = 0;

//     while (word[i])
//     {
//         if (word[i] != sepa)
//         {
//             result[j] = word[i];
//             j++;
//         }
//         i++;
//     }
//     result[j] = '\0';
//     return (result);
// }


// // int main (int ac, char **av , char**env)
// // {
    
// //     printf("thi si the %s\n", handling_qoutes("\"\'\"$user\'\"", '\"'));
// //     return 0;
// // }