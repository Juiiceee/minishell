/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:37:47 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:08:29 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printerr.h"

int	is_from_set(char c)
{
	char	*set;
	int		i;

	set = "cspdiuxX%";
	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

int	ft_printerr(const char *arg, ...)
{
	int		i;
	va_list	lst;
	int		retc;

	if (!arg)
		return (-1);
	va_start(lst, arg);
	i = 0;
	retc = 0;
	while (arg[i])
	{
		if (arg[i] == '%')
		{
			if (is_from_set(arg[i + 1]))
				retc += ft_tree(arg, i++, lst);
			else
				retc += print_char(arg[i]);
			i++;
		}
		else
			retc += print_char(arg[i++]);
	}
	va_end(lst);
	return (retc);
}
