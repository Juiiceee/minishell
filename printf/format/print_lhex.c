/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:13:38 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:39:02 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printerr.h"

static void	ft_putchar(char c)
{
	write(2, &c, 1);
}

static int	lennum(unsigned int n)
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
	while (n >= 16)
	{
		n /= 16;
		count++;
	}
	return (count);
}

int	print_lhex(unsigned int nbr)
{
	char	*base;
	int		ret;

	base = "0123456789abcdef";
	ret = lennum(nbr);
	if (nbr < 0)
	{
		nbr *= -1;
	}
	if (nbr >= 16)
	{
		print_lhex(nbr / 16);
	}
	ft_putchar(base[nbr % 16]);
	return (ret);
}
