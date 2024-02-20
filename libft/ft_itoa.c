/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:05:50 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:35 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lennum(long n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*tab;
	int		i;

	nb = (long) n;
	i = lennum(nb);
	tab = ft_calloc(sizeof (char), i + 1);
	if (!tab)
		return (NULL);
	tab[i] = '\0';
	if (nb < 0)
	{
		nb *= -1;
		tab[0] = '-';
	}
	while (i)
	{
		if (tab[i - 1] == '-')
			break ;
		tab[i - 1] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	return (tab);
}

// int main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%s",ft_itoa(atoi(argv[1])));
// 	return 0;
// }