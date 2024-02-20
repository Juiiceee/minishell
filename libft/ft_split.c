/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:35:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2024/02/20 13:02:16 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_charcount(char const *s, int index, char c)
{
	int	count;

	count = 0;
	while (s[index] && s[index] != c)
	{
		count++;
		index++;
	}
	return (count);
}

static char	*ft_strndup_custom(char const *s, int *retindex, int index, int n)
{
	int		i;
	char	*dup;

	i = 0;
	dup = malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (NULL);
	while (s[index] && i < n)
	{
		dup[i] = s[index];
		i++;
		index++;
	}
	*retindex = index;
	dup[i] = '\0';
	return (dup);
}

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		wordcount;
	char	**splitter;

	i = 0;
	j = 0;
	wordcount = ft_countword(s, c);
	splitter = malloc(sizeof(char *) * (wordcount + 1));
	if (!splitter)
		return (NULL);
	while (j < wordcount)
	{
		if (s[i] != c)
		{
			splitter[j] = ft_strndup_custom(s, &i, i, ft_charcount(s, i, c));
			if (!splitter[j++])
				return (ft_free(splitter), NULL);
		}
		i++;
	}
	splitter[j] = 0;
	return (splitter);
}

// int		main(int argc, char **argv)
// {
// 	char **split;
// 	int i = 0;
// 	(void)argc;
// 	(void)argv;

// 	// split = ft_split(strdup("Tripouille"), ' ');
// 	split = ft_split("  tripouille  42  ", ' ');

// 	while(split[i])
// 	{
// 		printf("%s\n", split[i]);
// 		i++;
// 	}
// 	printf("%s\n", split[i]);
// 	ft_free(split, 0);
// }
