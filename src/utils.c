/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 19:15:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/22 19:32:32 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*free_and_join(char *old, char *new)
{
	char	*tmp;

	tmp = ft_strjoin (old, new);
	free(old);
	free(new);
	return (tmp);
}