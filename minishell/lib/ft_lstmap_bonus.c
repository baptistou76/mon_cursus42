/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:31:53 by garside           #+#    #+#             */
/*   Updated: 2024/10/28 16:46:18 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*tmp;
	void	*content;

	dest = NULL;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		content = f(lst -> content);
		tmp = ft_lstnew(content);
		if (!tmp)
		{
			if (content)
				del(content);
			ft_lstclear(&dest, del);
			return (NULL);
		}
		ft_lstadd_back(&dest, tmp);
		lst = lst -> next;
	}
	return (dest);
}
