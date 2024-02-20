/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:14:45 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:35 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	int i = 0;
// 	while (i <= 1024)
// 	{
// 		// printf("%d\n",ft_isprint(i));
// 		// printf("%d\n",isprint(i));
// 		if (isprint(i) != ft_isprint(i))
// 		{
// 			printf("%s\n%d/%d\n","ERROR", ft_isprint(i), isprint(i));
// 			return(0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
