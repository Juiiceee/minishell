/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:10:11 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:39:02 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printerr.h"

static int	lennum(long n)
{
	int	count;

	count = 1;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count);
}

int	print_unbr(unsigned int nb)
{
	long	n;
	int		ret;

	n = (long) nb;
	ret = lennum(nb);
	if (n < 0)
	{
		n *= -1;
		print_char('-');
	}
	if (n >= 10)
	{
		print_nbr(n / 10);
		print_nbr(n % 10);
	}
	else
	{
		print_char(n + 48);
	}
	return (ret);
}
