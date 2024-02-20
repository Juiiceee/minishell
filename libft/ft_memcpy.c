/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:10:59 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:36 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		*(char *)dest = *(char *)src;
		i++;
		dest++;
		src++;
	}
	return (dest - i);
}

// #include <stdio.h>
// #include <string.h>

// int main (int argc, char **argv)
// {
// 	(void) argc;
// 	void *dest = NULL;
// 	void *desti = NULL;
// 	void *src = NULL;
// 	void *src = NULL;
//    return(0);
// }
