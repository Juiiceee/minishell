/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:06:00 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:35 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <ctype.h>
#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (8);
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <ctype.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	(void) argv;
// 	// int i = 0;
// 	// while (i <= 127)
// 	// {
// 	// 	printf("%d\n",ft_isalnum(i));
// 	// 	printf("%d\n",isalnum(i));
// 	// 	if (isalnum(i) != ft_isalnum(i))
// 	// 	{
// 	// 		printf("%s\n%d/%d\n","ERROR", ft_isalnum(i), isalnum(i));
// 	// 		return(0);
// 	// 	}
// 	// 	i++;
// 	// }
// 	return (0);
// }