/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:14:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 12:39:40 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token *listing_token(char **tmp)
{
	t_token *lst;
	t_token *new;
	int i;

	lst = NULL;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '>' || tmp[i][0] == '<')
		{
			new = tokenizing_redirect(tmp, &i);
			i += is_splitted(tmp[i]);
		}
		else if (tmp[i][0] == '|')
			new = tokenizing_pipe(tmp, &i);
		else
			new = tokenizing_other(tmp, &i);
		if (lst)
			tok_lstadd_back(&lst, new);
		else 
			lst = new;	
	}
	return (lst);	
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

t_token *ft_tokenizer(char *input)
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
	return (listing_token(tmp));
}
