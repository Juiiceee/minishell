/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:14:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/30 11:44:02 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_size(char *input, t_mini *mini)
{
	int		i;
	int		j;

	(void) mini;
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			j += escape_redirect(input, &i);
		else if (input[i] == '|')
		{
			while (input[i] == '|')
				i++;
			j++;
		}
		else if (input[i] == '\'' || input[i] == '\"')
			j += escape_quote(input, &i);
		else
			j += escape_word(input, &i, mini);
		while (ft_isspace(input[i]))
			i++;
	}
	return (j);
}

char	*split_env(char *old, char **tmp, int *j)
{
	char	**spli;
	int		i;
	int		tmp_j;
	char	*buff;

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
	buff = (ft_strdup(spli[0]));
	free(old);
	ft_free(spli);
	return (buff);
}

t_token	*listing_token(char **tmp)
{
	t_token	*lst;
	t_token	*new;
	int		i;

	lst = NULL;
	i = 0;
	while (tmp[i])
	{
		if (tmp[i][0] == '>' || tmp[i][0] == '<')
		{
			new = tokenizing_redirect(tmp, &i);
			i += is_splitted(tmp, &i);
		}
		else if (tmp[i][0] == '|')
			new = tokenizing_pipe(tmp, &i);
		else
			new = tokenizing_other(tmp, &i);
		new->next = NULL;
		if (lst)
			tok_lstadd_back(&lst, new);
		else
			lst = new;
	}
	free(tmp);
	return (lst);
}

char	*ft_select_token(char *input, int *i, t_mini *mini, int *j)
{
	if (input[*i] == '$' || input[*i] == '|'
		|| input[*i] == '>' || input[*i] == '<')
		return (punct_parse(input + *i, i, mini, j));
	else if (input[*i] == '"')
		return (dquote_parse((input + *i), i, mini));
	else if (input[*i] == '\'')
		return (squote_parse((input + *i), i));
	else if (ft_isprint(input[*i]))
		return (str_parse(input + *i, i));
	return (NULL);
}

t_token	*ft_tokenizer(char *input, t_mini *mini)
{
	int		i;
	int		j;
	int		inpt_size;

	j = 0;
	i = 0;
	inpt_size = input_size(input, mini);
	mini->tabcmd = ft_calloc(sizeof (char *), (inpt_size + 1));
	while (input[i] != '\0')
	{
		if (!ft_isspace(mini->input[i]) && mini->input[i] != '\0')
		{
			mini->tabcmd[j] = ft_select_token(input, &i, mini, &j);
			while (!ft_isspace(input[i]) && input[i] != '\0' && input[i] != '<'
				&& input[i] != '>' && input[i] != '|' && mini->tabcmd[j]
				&& mini->tabcmd[j][0] != '|')
				mini->tabcmd[j] = free_and_join(mini->tabcmd[j],
						ft_select_token(input, &i, mini, &j));
			while (mini->tabcmd[j] && j < inpt_size)
				j++;
		}
		if (mini->input[i] != '\0' && ft_isspace(mini->input[i]))
			i++;
	}
	return (listing_token(mini->tabcmd));
}
