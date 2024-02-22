/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:14:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/22 19:25:26 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *ft_select_token(char *input, int *i)
{
	char *tmp;
	if (isalpha(input[*i]))
		return(str_parse(input + *i, i));
	else if (input[*i] == '"')
		return(dquote_parse((input + *i + 1), i));
	else if (input[*i] == '\'')
		return(squote_parse((input + *i + 1), i));
	else if (ispunct(input[*i]) && !isspace(input[*i]))
		return(punct_parse(input + *i, i));
	return "CACA";
}


void ft_tokenizer(char *input, t_mini *mini)
{
	int i;
	int j;
	char *tmp[1024];
	char *old;
	
	j = 0;
	i = 0;
	while(input[i] != '\0')
	{
		if (!isspace(input[i]) && input[i] != '\0')
		{
			old = ft_select_token(input, &i);
			while (!isspace(input[i]) && input[i] != '\0')
				old = free_and_join(old, ft_select_token(input, &i));
			tmp[j++] = old;
		}
		if (input[i] != '\0')
			i++;
	}
	tmp[j] = 0;
	for (size_t k = 0; tmp[k]; k++)
		printf("%s\n", tmp[k]);	
}