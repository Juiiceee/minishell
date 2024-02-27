/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 16:30:36 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/27 13:17:43 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_exec(t_mini *mini)
{
	t_token *tmp;
	
	tmp = mini->lst;
	mini->exe = NULL;
	while (tmp)
	{
		exe_lstadd_back(&mini->exe, exe_lstnew(tmp));
		while (tmp->data_type != PIPE)
			if (tmp->next == NULL)
				break ;
			else 
				tmp = tmp->next;
		if (tmp->data_type == PIPE)
			if (tmp->next == NULL)
				break ;
			else 
				tmp = tmp->next;
		if (tmp->next == NULL)
			break ;
	}
	for (size_t i = 0; mini->exe ; i++)
	{
		printf("%s\n", mini->exe->cmd[0]);
		if (mini->exe->in)
		printf("%s\n", mini->exe->in[0]);
		if (mini->exe->out)
		printf("%s\n", mini->exe->out[0]);
		mini->exe = mini->exe->next;
	}
}
