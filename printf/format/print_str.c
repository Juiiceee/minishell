/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:07:55 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:39:02 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printerr.h"

int	print_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write(2, "(null)", 6);
		return (6);
	}
	while (str[i])
		print_char(str[i++]);
	return (i);
}
