/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printerr_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:05:14 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:08:28 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printerr.h"

int	ft_tree(const char *str, int i, va_list lst)
{
	int	count;

	i++;
	count = 0;
	if (str[i] == 'c')
		count = print_char(va_arg(lst, int));
	if (str[i] == 's')
		count = print_str(va_arg(lst, char *));
	if (str[i] == 'p')
		count = print_pointer(va_arg(lst, void *));
	if (str[i] == 'd' || str[i] == 'i')
		count = print_nbr(va_arg(lst, int));
	if (str[i] == 'u')
		count = print_unbr(va_arg(lst, int));
	if (str[i] == 'x')
		count = print_lhex(va_arg(lst, int));
	if (str[i] == 'X')
		count = print_uhex(va_arg(lst, int));
	if (str[i] == '%')
		count = print_char('%');
	return (count);
}
