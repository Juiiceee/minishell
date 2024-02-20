/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:13:49 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/10 15:52:46 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_calloc(1, 1));
	s += start;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub = malloc((sizeof (char)) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && s[i])
	{
		sub[i] = s[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	printf("%s", ft_substr("Lorem ipsum dolores et ta soeur", 7 , 10));
// 	return(0);
// }