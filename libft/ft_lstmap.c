/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-cunh <mda-cunh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 21:45:25 by mda-cunh          #+#    #+#             */
/*   Updated: 2023/11/10 15:46:54 by mda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*sav;

	newlst = NULL;
	if (!lst || !del || !f)
		return (NULL);
	while (lst)
	{
		sav = ft_lstnew((*f)(lst->content));
		if (!sav)
		{
			ft_lstclear(&newlst, *del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, sav);
		lst = lst->next;
	}
	return (newlst);
}
