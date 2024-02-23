/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenier.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:14:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/23 19:47:54 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *listing_token(char **tmp)
{
	t_token *buff;
	int i;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '>' || tmp[i][0] == '<')
			tokenizing_redirect(tmp, &i, &buff);
		if (tmp[i][0] == '|')
			;// tokenizing_pipe(tmp, &i, &buff);
		if (ft_isalpha(tmp[i][0]))
			;// tokenizing_char(tmp, &i, &buff);			
		printf("%s\n", buff->global[0]);
	}
	return (NULL);	
}

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
	return (NULL);
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
			while (!isspace(input[i]) && input[i] != '\0' && old[0] != '|')
				old = free_and_join(old, ft_select_token(input, &i));
			if (old)
				tmp[j++] = old;
		}
		if (input[i] != '\0' && isspace(input[i]))
			i++;
	}
	tmp[j] = 0;
	listing_token(tmp);
}
