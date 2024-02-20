/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:43:30 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:35 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		sync;
	char	car;

	i = 0;
	sync = 0;
	car = (char) c;
	while (s[i])
	{
		if (s[i] == car)
			sync = i;
		i++;
		if (s[i] == car)
			sync = i;
	}
	if (sync > 0)
		return ((char *)s + sync);
	if ((sync == 0) && (s[0] == car))
		return ((char *)s);
	return (0);
}
