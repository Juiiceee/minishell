/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:45:28 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/10 16:10:12 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*alloc;

	if ((size * nmemb) >= SIZE_MAX)
		return (NULL);
	if ((int) nmemb < 0 && (int) size < 0)
		return (NULL);
	if ((int)(size * nmemb) < 0)
		return (NULL);
	alloc = malloc(nmemb * size);
	if (!alloc)
		return (NULL);
	ft_bzero(alloc, nmemb * size);
	return (alloc);
}
// 
// #include <stdio.h>
// #include <stdlib.h>
// 
// int main(int argc, char **argv)
// {
	// (void) argc;		
	// void *ptr_call;
	// void *ptr_cacalloc;
	// size_t nmemb = SIZE_MAX;
	// ptr_call = calloc(atoi(argv[1]), atoi(argv[2]));
	// ptr_cacalloc = ft_calloc(atoi(argv[1]), atoi(argv[2]));
// 
	// printf("%p\n/%p\n", ptr_call ,ptr_cacalloc);
	// free(ptr_cacalloc);
	// free(ptr_call);
// }