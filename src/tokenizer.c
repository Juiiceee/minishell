/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:14:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 12:34:20 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	input_size(char *input, t_mini *mini)
{
	(void) mini;
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

char	*split_env(char *old, char **tmp, int *j)
{
	char **spli;
	int i;
	int tmp_j;

	tmp_j = *j;
	tmp_j += 1;
	i = 1;
	spli = ft_split(old + 1, ' ');
	if (!spli)
		return (NULL);	
	while (i <= ft_tablen(spli) - 1)
	{
		tmp[tmp_j] = ft_strdup(spli[i]);
		tmp_j = tmp_j + 1;
		i++;
	}
	return(ft_strdup(spli[0]));
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

char *ft_select_token(char *input, int *i, t_mini *mini, int *j)
{
	if (input[*i] == '$' || input[*i] == '|' || input[*i] == '>' || input[*i] == '<')
		return(punct_parse(input + *i, i, mini, j));
	else if (input[*i] == '"')
		return(dquote_parse((input + *i + 1), i));
	else if (input[*i] == '\'')
		return(squote_parse((input + *i + 1), i));
	else if (ft_isprint(input[*i]))
		return(str_parse(input + *i, i));
	return (NULL);
}

t_token *ft_tokenizer(char *input, t_mini *mini)
{
	int i;
	int j;
	char *old;
	
	j = 0;
	i = 0;
	mini->tabcmd = ft_calloc(sizeof (char *), (input_size(input, mini) + 1));
	while(input[i] != '\0')
	{
		if (!isspace(mini->input[i]) && mini->input[i] != '\0')
		{
			old = ft_select_token(input, &i, mini, &j);
			if (old && old[0] != '$')
				mini->tabcmd[j] = old;
			while (!isspace(input[i]) && input[i] != '\0' && old[0] != '|')
				mini->tabcmd[j] = free_and_join(mini->tabcmd[j], ft_select_token(input, &i, mini, &j));
			while (mini->tabcmd[j])
				j++;
		}
		if (mini->input[i] != '\0' && isspace(mini->input[i]))
			i++;
	}
	return (listing_token(mini->tabcmd));
}
