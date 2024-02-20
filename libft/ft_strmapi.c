/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@42paris.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:51:16 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/07 22:31:35 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dump;

	i = 0;
	if (!s || !f)
		return (NULL);
	dump = malloc((sizeof (char)) * ft_strlen(s) + 1);
	if (!dump)
		return (NULL);
	while (s[i])
	{
		dump[i] = (*f)(i, s[i]);
		i++;
	}
	dump[i] = '\0';
	return (dump);
}
