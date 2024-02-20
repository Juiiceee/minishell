/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 19:11:56 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/10 15:52:19 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	is_from_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimed;
	size_t	start_trim;
	size_t	end_trim;
	size_t	i;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	start_trim = 0;
	end_trim = ft_strlen(s1);
	while (s1[start_trim] && is_from_set(s1[start_trim], set))
		start_trim++;
	while (end_trim > start_trim && is_from_set(s1[end_trim - 1], set))
		end_trim--;
	trimed = malloc((sizeof (char)) * (end_trim - start_trim + 1));
	if (!trimed)
		return (NULL);
	while (start_trim < end_trim)
	{
		trimed[i] = s1[start_trim];
		i++;
		start_trim++;
	}
	trimed[i] = '\0';
	return (trimed);
}

// int main(void)
// {	
// 	char *s1 = "me !\n   \n \n \t\t\n  ";
// 	// char *s2 = "Hello \t  Please\n Trim me !";

// 	printf("%s", ft_strtrim(s1, "\n\t"));
// 	return(0);
// }