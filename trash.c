// char *take_expand(char *input, t_env *env, t_token *token)
// {
//     int i = 0, start = 0;
//     char quote = 0;
//     char *result = ft_strdup("");
//     char *before;
//     t_token *new_token;
//     // char *input;
//     // input = ft_handel_qoute(inh);
//     while (input[i])
//     {
//         if ((input[i] == '\'' || input[i] == '"') && quote == 0)
//             quote = input[i];
//         else if (input[i] == quote)
//             quote = 0;

//         if (input[i] == '$' && quote != '\'')
//         {
//             // printf("\tso this is i %d andddd %d the start\n", i, start);
//             if (i > start)
//             {
//                 before = ft_substr(input, start, i - start);
//                 printf("this si first |%s|\n", before);
//                 result = ft_strjoin_free(result, before);
//             }
//             // printf("thi sis the right things |%s|\n", result);
//             // printf("---------------------%s\n", result);
//             int help;
//             char *repl = take_replace(i, input, &help, env);
//             char *take = ft_strjoin(result, repl);
//             // take = ft_strjoin(take, las)
//             if (quote == 0)
//             {
//                 char **words = ft_split(take, ' ');
//                 if (words[0])
//                 {
//                     if (*result == '\0')
//                     {
//                         result = ft_strjoin_free(result, ft_strdup(words[0]));
//                     }
//                     else
//                     {
//                         t_token *new_token = create_token(words[0]);
//                         insert_token_after(token, new_token);
//                         token = new_token;
//                     }
//                 }
                
//                 for (int j = 1; words[j]; j++)
//                 {
//                     // printf("firrst|%s|\n", words[j]);
//                     new_token = create_token(ft_handel_qoute(words[j]));
//                     insert_token_after(token, new_token);
//                     token = new_token;
//                 }
                
//                 free_str_array(words);
//                 free(repl);
//                 i++;
//             }
//             else
//             {
//                 result = ft_strjoin_free(result, repl);
//             }
            
//             i = help;
//             start = i;
//         }
//         else
//         {
//             // printf("%c\n", input[i]);
//             i++;
//         }
//     }
    
//     if (i > start)
//     {
//         char *last = ft_substr(input, start, i - start);
//         // printf("this is the result beffor %s|||| %s\n", result ,last);
//         result = ft_strjoin_free(result, last);
//     }
//     return result;
// }

// char *take_expand(char *input, t_env *env, t_token *token)
// {
//     int i = 0, start = 0;
//     char quote = 0;
//     char *result = ft_strdup("");
//     char *before;
//     t_token *new_token;

//     while (input[i])
//     {
//         // Handle quote tracking
//         if ((input[i] == '\'' || input[i] == '"') && quote == 0)
//             quote = input[i];
//         else if (input[i] == quote)
//             quote = 0;

//         // Handle variable expansion
//         if (input[i] == '$' && quote != '\'')
//         {
//             if (i > start)
//             {
//                 before = ft_substr(input, start, i - start);
//                 result = ft_strjoin_free(result, before);
//             }

//             // Expand the variable
//             int end_pos;
//             char *repl = take_replace(i, input, &end_pos, env);
            
//             // If we're inside quotes, just concatenate
//             if (quote != 0)
//             {
//                 result = ft_strjoin_free(result, repl);
//                 // free(repl);
//             }
//             else
//             {
//                 // For unquoted expansion, handle word splitting carefully
//                 char *combined = ft_strjoin(result, repl);
//                 // free(result);
//                 // free(repl);
//                 result = combined;
//             }
            
//             i = end_pos;
//             start = i;
//         }
//         else
//         {
//             i++;
//         }
//     }

//     // Add remaining content
//     if (i > start)
//     {
//         char *last = ft_substr(input, start, i - start);
//         result = ft_strjoin_free(result, last);
//     }

//     // Only create new tokens if we're not in a quoted context
//     if (quote == 0)
//     {
//         // Split into words only for unquoted expansions
//         char **words = ft_split(result, ' ');
//         if (words[0])
//         {
//             // First word goes to current token
//             free(result);
//             result = ft_strdup(words[0]);
            
//             // Additional words become new tokens
//             for (int j = 1; words[j]; j++)
//             {
//                 new_token = create_token(words[j]);
//                 insert_token_after(token, new_token);
//                 token = new_token;
//             }
//         }
//         // free_str_array(words);
//     }

//     return result;
// }

// char *take_expand(char *input, t_env *env, t_token *token)
// {
//     int i = 0, start = 0;
//     char quote = 0;
//     char *result = ft_strdup("");
//     char *before;
//     t_token *new_token = NULL;
//     int in_dquotes = 0;

//     while (input[i])
//     {
//         if ((input[i] == '\'' || input[i] == '"') && quote == 0)
//         {
//             quote = input[i];
//             in_dquotes = (input[i] == '"');
//         }
//         else if (input[i] == quote)
//         {
//             quote = 0;
//             in_dquotes = 0;
//         }

//         if (input[i] == '$' && quote != '\'')
//         {
//             if (i > start)
//             {
//                 before = ft_substr(input, start, i - start);
//                 result = ft_strjoin_free(result, before);
//             }

//             int end_pos;
//             char *repl = take_replace(i, input, &end_pos, env);
            
//             // Always preserve exact content inside double quotes
//             if (in_dquotes || quote == '"')
//             {
//                 result = ft_strjoin_free(result, repl);
//                 // free(repl);
//             }
//             else
//             {
//                 // For unquoted expansion, handle word splitting
//                 char **words = ft_split(repl, ' ');
//                 if (words[0])
//                 {
//                     result = ft_strjoin_free(result, ft_strdup(words[0]));
//                     for (int j = 1; words[j]; j++)
//                     {
//                         new_token = create_token(words[j]);
//                         insert_token_after(token, new_token);
//                         token = new_token;
//                     }
//                 }
//                 // free_str_array(words);
//                 // free(repl);
//             }
            
//             i = end_pos;
//             start = i;
//         }
//         else
//         {
//             i++;
//         }
//     }

//     if (i > start)
//     {
//         char *last = ft_substr(input, start, i - start);
//         // result = ft_strjoin_free(result, last);
//     }

//     // If we ended in double quotes, don't split the result
//     if (!in_dquotes && quote == 0)
//     {
//         char **words = ft_split(result, ' ');
//         if (words[0])
//         {
//             // free(result);
//             result = ft_strdup(words[0]);
//             for (int j = 1; words[j]; j++)
//             {
//                 new_token = create_token(words[j]);
//                 insert_token_after(token, new_token);
//                 token = new_token;
//             }
//         }
//         // free_str_array(words);
//     }

//     return result;
// }

