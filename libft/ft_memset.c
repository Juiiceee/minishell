/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:30:32 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:36:00 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)str = c;
		i++;
		str++;
	}
	return (str - i);
}

// #include <stdio.h>
// #include <string.h>

// int main (void) 
// {
//    char *ste = NULL;
//    char *str = NULL;
//    printf("%p\n",ft_memset(ste,'e',42));

//    printf("%p\n",memset(str,'e',42));
//    return(0);
// }
