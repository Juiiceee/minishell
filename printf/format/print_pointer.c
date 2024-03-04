/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:14:46 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/03/04 13:39:02 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printerr.h"

static int	lennum(size_t n)
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

static int	print_phex(size_t nbr)
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
		print_phex(nbr / 16);
	}
	print_char(base[nbr % 16]);
	return (ret);
}

int	print_pointer(void *ptr)
{
	size_t	*i;
	int		count;

	i = (size_t *)&ptr;
	if (i[0] == 0)
	{
		write(2, "(nil)", 5);
		return (5);
	}
	count = 2;
	write(2, "0x", 2);
	count += print_phex(i[0]);
	return (count);
}
