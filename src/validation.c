/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:42:29 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/04/30 11:46:32 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_inpt_error(t_mini *mini)
{
	free(mini->input);
	ft_tokclear_str(&mini->lst);
}

int	input_validation(t_mini *mini)
{
	t_token	*tmp;

	tmp = mini->lst;
	if (!tmp || (mini->lst->global && !ft_strlen(mini->lst->global[0])))
		return (1);
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
	return (0);
}

int	exec_validation(t_mini *mini)
{
	t_exec	*tmp;

	tmp = mini->exe;
	while (tmp)
	{
		if (tmp->cmd == NULL)
		{
			ft_execlear(&mini->exe, *ft_free);
			free(mini->input);
			ft_tokclean(&mini->lst);
			return (1);
		}	
		tmp = tmp->next;
	}
	return (0);
}
