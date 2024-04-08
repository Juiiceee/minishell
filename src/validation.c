/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:42:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/08 16:19:30 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_inpt_error(t_mini *mini)
{
		free(mini->input);
		ft_tokclean(&mini->lst);
}

int input_validation(t_mini *mini)
{
	t_token *tmp;
	tmp = mini->lst;
	if (mini->lst->data_type == PIPE)
		return (1);
	while (tmp != NULL)
	{
		if (tmp->data_type == DONT_EXIST)
			return (1);
		else if ((tmp->data_type == PIPE) && (!tmp->next 
				|| tmp->next->data_type == PIPE))
			return (1);
		tmp = tmp->next;
	}
	return(0);
}