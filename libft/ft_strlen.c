/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:17:31 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/24 10:15:50 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (*s)
	{
		s++;
		count++;
	}
	return (count);
}

// #include <stdio.h>
// #include <string.h>

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	void *tab = NULL; 

// 	printf("%ld\n",ft_strlen(tab));
// 	printf("%ld\n",strlen(tab));

// 	return (0);
//  }
