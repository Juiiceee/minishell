/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   punct_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:50:42 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/23 12:10:10 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char 	*pipe_sign(char *input, int *i)
{
	int j;
	char *tmp;


	j = 0;
	while (input[j] == '|')
		j++;
	*i += j;
	tmp = ft_substr(input, 0,  j);
	return (tmp);
}

char 	*redirect_sign(char *input, int *i)
{
	int j;
	char *tmp;


	j = 0;
	while (input[j] == '<' || input[j] == '>')
		j++;
	*i += j;
	tmp = ft_substr(input, 0,  j);
	return (tmp);
}

char 	*dollar_sign(char *input, int *i)
{
	int		j;
	int		k;
	char	*tmp;

	j = 1;
	k = -1;
	*i += 1;
	if (isspace(input[1]))
		return (ft_strdup("$"));
	while (isalpha(input[j]) && input[j])
		j++;
	tmp = malloc((sizeof (char)) * j);
	while (++k < j - 1)
		tmp[k] = input[k + 1];
	tmp[k] = '\0';
	*i += ft_strlen(tmp);
	if (!getenv(tmp))
		return (free(tmp), NULL);
	else 
		tmp = ft_strdup(getenv(tmp));
	return(tmp);
}