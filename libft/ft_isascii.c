/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:09:59 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:35 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
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
// 	while (i <= 255)
// 	{
// 		// printf("%d\n",ft_isascii(i));
// 		// printf("%d\n",isascii(i));
// 		if (isascii(i) != ft_isascii(i))
// 		{
// 			printf("%s\n%d/%d\n","ERROR", ft_isascii(i), isascii(i));
// 			return(0);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
