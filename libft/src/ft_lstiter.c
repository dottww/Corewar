/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cseguier <cseguier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 13:29:54 by cseguier          #+#    #+#             */
/*   Updated: 2020/07/20 15:30:49 by cseguier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_lftlist *lst, void (*f)(t_lftlist *elem))
{
	t_lftlist	*list;

	while (lst)
	{
		list = lst->next;
		f(lst);
		lst = list;
	}
}
