/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:14:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/02 11:14:39 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_size(char *input)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			j += escape_redirect(input, &i);
		else if (input[i] == '|')
		{
			while(input[i] == '|')
				i++;
			j++;
		}
		else if (input[i] == '\'' || input[i] == '\"')
			j += escape_quote(input, &i);
		else 
			j += escape_word(input, &i);
		while (isspace(input[i]))
			i++;
	}
	return (j);
}

void split_env(char *old, char **tmp, int *j)
{
	char **spli;
	int i;

	i = 0;	
	spli = ft_split(old + 1, ' ');
	if (!spli)
		return ;	
	while (i <= ft_tablen(spli) - 1)
	{
		tmp[*j] = ft_strdup(spli[i]);
		*j = *j + 1;
		i++;
	}
	tmp[*j] = NULL;
}

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
	if (input[*i] == '$' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		return(punct_parse(input + *i, i));
	else if (input[*i] == '"')
		return(dquote_parse((input + *i + 1), i));
	else if (input[*i] == '\'')
		return(squote_parse((input + *i + 1), i));
	else if (ft_isprint(input[*i]))
		return(str_parse(input + *i, i));
	return (NULL);
}

t_token *ft_tokenizer(char *input)
{
	int i;
	int j;
	char **tmp;
	char *old;
	
	j = 0;
	i = 0;
	tmp = malloc((sizeof (char *)) * input_size(input) + 99991);
	while(input[i] != '\0')
	{
		if (!isspace(input[i]) && input[i] != '\0')
		{
			old = ft_select_token(input, &i);
			if (old[0] == '$')
				split_env(old, tmp, &j);
			while (!isspace(input[i]) && input[i] != '\0' && old[0] != '|')
				old = free_and_join(old, ft_select_token(input, &i));
			if (old && old[0] != '$')
				tmp[j++] = old;
		}
		if (input[i] != '\0' && isspace(input[i]))
			i++;
	}
	tmp[j] = 0;
	return (listing_token(tmp));
}
